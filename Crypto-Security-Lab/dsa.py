import hashlib
import random


q = 23  
p = 11 * q + 1  
g = 2  


private_key = random.randint(1, q - 1)  
public_key = pow(g, private_key, p)  

print(f"Private Key: {private_key}")
print(f"Public Key: {public_key}")

def sign_message(message):
    """
    Sign a message using the private key.
    """
    
    hashed_message = int(hashlib.sha256(message.encode()).hexdigest(), 16)

    
    k = random.randint(1, q - 1)
    while hashlib.gcd(k, q) != 1:
        k = random.randint(1, q - 1)

    
    r = pow(g, k, p) % q
    k_inv = pow(k, -1, q)  
    s = (k_inv * (hashed_message + private_key * r)) % q

    return r, s

def verify_signature(message, r, s):
    """
    Verify the signature of a message using the public key.
    """
    
    hashed_message = int(hashlib.sha256(message.encode()).hexdigest(), 16)

    
    if not (0 < r < q and 0 < s < q):
        return False

    
    w = pow(s, -1, q)  
    u1 = (hashed_message * w) % q
    u2 = (r * w) % q

    
    v = ((pow(g, u1, p) * pow(public_key, u2, p)) % p) % q

    
    return v == r



message = "This is a test message."
r, s = sign_message(message)
print(f"Signature: (r={r}, s={s})")


is_valid = verify_signature(message, r, s)
print(f"Signature valid: {is_valid}")
