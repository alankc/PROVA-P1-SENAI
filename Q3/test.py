import unittest
from lib.Q3 import MyAES_ECB 

class TestMyAES_ECB(unittest.TestCase):
    
    def setUp(self):
        # This is run before each test
        self.key = "thisisasecretkey"
        self.invalid_key = "shor_tkey"
        self.aes_ecb = MyAES_ECB(self.key)

        self.long_msg = "Test Msg with several letters"
        self.short_msg = "MSG"
    
    def test_init(self):
        # Test if initialization works
        self.assertIsInstance(self.aes_ecb, MyAES_ECB)

    def test_init_with_invalid_key(self):
        # Test initialization with invalid key
        with self.assertRaises(RuntimeError) as context:
            MyAES_ECB(self.invalid_key)
        self.assertEqual(str(context.exception), "Key must have 16 characters!")
    
    def test_encrypt_raises_runtime_error_if_cipher_not_defined(self):
        # Test that encrypt_msg raises RuntimeError if cipher is None
        aes_ecb_invalid = MyAES_ECB(self.key)
        aes_ecb_invalid._cipher = None  # Simulate uninitialized cipher
        with self.assertRaises(RuntimeError) as context:
            aes_ecb_invalid.encrypt_msg("just_a_test")
        self.assertEqual(str(context.exception), "Cipher not defined")

    def test_decrypt_raises_runtime_error_if_cipher_not_defined(self):
        # Test that decrypt_msg raises RuntimeError if cipher is None
        aes_ecb_invalid = MyAES_ECB(self.key)
        aes_ecb_invalid._cipher = None  # Simulate uninitialized cipher
        with self.assertRaises(RuntimeError) as context:
            aes_ecb_invalid.decrypt_msg("just_a_test")
        self.assertEqual(str(context.exception), "Cipher not defined")

    def test_encrypt_decrypt_msg_formats_short_msg(self):
        # Test that a msg can be encrypted and then decrypted back to original
        # Also checks if encrypted and decrypted are strings
        encrypted_msg = self.aes_ecb.encrypt_msg(self.short_msg)
        decrypted_msg = self.aes_ecb.decrypt_msg(encrypted_msg)
        self.assertIsInstance(encrypted_msg, str)
        self.assertIsInstance(decrypted_msg, str)
        self.assertEqual(decrypted_msg, self.short_msg)

    def test_encrypt_decrypt_msg_formats_long_msg(self):
        # Test that a msg can be encrypted and then decrypted back to original
        # Also checks if encrypted and decrypted are strings
        encrypted_msg = self.aes_ecb.encrypt_msg(self.long_msg)
        decrypted_msg = self.aes_ecb.decrypt_msg(encrypted_msg)
        self.assertIsInstance(encrypted_msg, str)
        self.assertIsInstance(decrypted_msg, str)
        self.assertEqual(decrypted_msg, self.long_msg)

    def test_decript_non_hexdacimal_number(self):
        # Test msg with trash data
        encrypted_msg = self.aes_ecb.encrypt_msg(self.short_msg)
        with self.assertRaises(ValueError) as context:
            decrypted_msg = self.aes_ecb.decrypt_msg(encrypted_msg + str("trashing the format"))
        self.assertIn("non-hexadecimal number found in fromhex", str(context.exception))

if __name__ == "__main__":
    unittest.main()
