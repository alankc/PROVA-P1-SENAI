from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad

class MyAES_ECB:
    def __init__(self, key: str):

        self._cipher = None
        if len(key) != 16:
            raise RuntimeError("Key must have 16 characters!")
        # receives bytes, mode(Literal)
        self._cipher = AES.new(key.encode('utf-8'), AES.MODE_ECB)

    def decrypt_msg(self, encrypted_msg: str) -> str:
        if not self._cipher:
            raise RuntimeError("Cipher not defined")
        
        # decrypt needs to receive a vector of bytes representing the hexadecimal number from the encrypted msg
        decrypted_bytes = self._cipher.decrypt(bytes.fromhex(encrypted_msg))
        decrypted_bytes = unpad(decrypted_bytes, AES.block_size)

        return str(decrypted_bytes.decode("utf-8"))
            
    def encrypt_msg(self, msg: str) -> str:
        if not self._cipher:
            raise RuntimeError("Cipher not defined")
        
        # msgs need to have size multiple of block size. pad functions does that
        padded_msg = pad(msg.encode("utf-8"), AES.block_size)
        
        encrypted_bytes = self._cipher.encrypt(padded_msg)
        
        # returns the string of hexadecimal numbers
        return encrypted_bytes.hex()
        

if __name__ == '__main__':

    '''
    BASIC INITIAL TESTS
    '''
    encrypted_msg = "a57fd9725fb53c53d5bd0b56185da50f70ab9baea5a43523b76c03e3eb989a20"
    myaes_ecb = MyAES_ECB("thisisasecretkey")

    try:
        decrypted_msg = myaes_ecb.decrypt_msg(encrypted_msg)
        print(f"decrypted msg: ==>{decrypted_msg}<==")
        
        assert decrypted_msg == "Sistemas Embarcados"
        assert myaes_ecb.encrypt_msg(decrypted_msg) == encrypted_msg

    except ValueError:
        print("Key incorrect or message corrupted")