import queue

class SecureChatApp:
    def __init__(self, master, config):
        self.master = master
        master.title("Two-Party Secure Chat")

        self.config = config
        self.my_priv = load_rsa_private_key(config['my_private_key'])
        self.my_pub  = load_rsa_public_key(config['my_public_key'])
        self.peer_pub = load_rsa_public_key(config['peer_public_key'])

        # GUI
        top = Frame(master)
        top.pack(fill=BOTH, expand=True, padx=6, pady=6)

        Label(top, text="Received Messages:").pack(anchor='w')
        self.recv_text = Text(top, height=20, wrap='word')
        self.recv_text.pack(side=LEFT, fill=BOTH, expand=True)
        scroll = Scrollbar(top, command=self.recv_text.yview)
        scroll.pack(side=RIGHT, fill=Y)
        self.recv_text['yscrollcommand'] = scroll.set
        self.recv_text.config(state='normal')

        bottom = Frame(master)
        bottom.pack(fill=BOTH, padx=6, pady=(0,6))

        Label(bottom, text="Type message:").pack(anchor='w')
        self.entry = Entry(bottom, width=80)
        self.entry.pack(side=LEFT, fill=BOTH, expand=True, padx=(0,6))
        self.send_button = Button(bottom, text="Send", command=self.on_send)
        self.send_button.pack(side=LEFT)

        self.status = Label(master, text="Status: Ready")
        self.status.pack(anchor='w', padx=6, pady=(0,6))

        # --- NEW: message queue for thread-safe GUI updates
        self.msg_queue = queue.Queue()

        # Start listening thread
        self.listener_thread = threading.Thread(target=self.listen_loop, daemon=True)
        self.listener_thread.start()

        # Start polling the queue
        self.master.after(100, self.process_incoming)

    def append_received(self, text):
        self.recv_text.insert(END, text + "\n")
        self.recv_text.see(END)

    def process_incoming(self):
        """Poll queue for new messages and update GUI"""
        while not self.msg_queue.empty():
            msg = self.msg_queue.get()
            self.append_received(msg)
        self.master.after(100, self.process_incoming)

    def listen_loop(self):
        """Continuously accept connections and hand off to handler threads."""
        listen_ip = self.config.get('listen_ip', '0.0.0.0')
        listen_port = int(self.config['listen_port'])
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server:
            server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            server.bind((listen_ip, listen_port))
            server.listen(5)
            print(f"Listening on {listen_ip}:{listen_port}")
            while True:
                try:
                    conn, addr = server.accept()
                    threading.Thread(target=self.handle_client, args=(conn, addr), daemon=True).start()
                except Exception as e:
                    print("Listener exception:", e)
                    traceback.print_exc()

    def handle_client(self, conn, addr):
        with conn:
            try:
                header = recv_all(conn, 4)
                length = int.from_bytes(header, 'big')
                payload_bytes = recv_all(conn, length)
                payload = json.loads(payload_bytes.decode('utf-8'))

                enc_session_key = base64.b64decode(payload['enc_session_key'])
                iv = base64.b64decode(payload['iv'])
                ciphertext = base64.b64decode(payload['ciphertext'])
                tag = base64.b64decode(payload['tag'])

                session_key = decrypt_session_key_with_rsa(enc_session_key, self.my_priv)
                plaintext = aes_decrypt_gcm(iv, ciphertext, tag, session_key)
                text = plaintext.decode('utf-8', errors='replace')

                sender_info = f"[{addr[0]}:{addr[1]}]"
                self.msg_queue.put(f"{sender_info} {text}")
                self.master.after(0, lambda: self.status.config(text=f"Received message from {addr[0]}"))

            except Exception as e:
                err_msg = f"[Receive error from {addr}] {e}"
                self.msg_queue.put(err_msg)
                self.master.after(0, lambda: self.status.config(text="Status: Receive error"))

