
local crypto = {}

function crypto.encryptAES256(plaintext, key)
    return CCCrypto:encryptAES256(plaintext, string.len(plaintext), key, string.len(key))
end

function crypto.decryptAES256(ciphertext, key)
    return CCCrypto:decryptAES256(ciphertext, string.len(ciphertext), key, string.len(key))
end

function crypto.encryptXXTEA(plaintext, key)
    return CCCrypto:encryptXXTEA(plaintext, string.len(plaintext), key, string.len(key))
end

function crypto.decryptXXTEA(ciphertext, key)
    return CCCrypto:decryptXXTEA(ciphertext, string.len(ciphertext), key, string.len(key))
end

function crypto.encodeBase64(plaintext)
    return CCCrypto:encodeBase64(plaintext, string.len(plaintext))
end

function crypto.decodeBase64(ciphertext)
    return CCCrypto:decodeBase64(ciphertext)
end

function crypto.md5(input, isRawOutput)
    if type(isRawOutput) ~= "boolean" then isRawOutput = false end
    return CCCrypto:MD5(input, isRawOutput)
end

function crypto.md5file(path)
    return CCCrypto:MD5File(path)
end

return crypto
