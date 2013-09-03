
local crypto = {}

function crypto.encryptAES256(plaintext, key)
    return cc.CCCrypto:encryptAES256(plaintext, string.len(plaintext), key, string.len(key))
end

function crypto.decryptAES256(ciphertext, key)
    return cc.CCCrypto:decryptAES256(ciphertext, string.len(ciphertext), key, string.len(key))
end

function crypto.encryptXXTEA(plaintext, key)
    return cc.CCCrypto:encryptXXTEA(plaintext, string.len(plaintext), key, string.len(key))
end

function crypto.decryptXXTEA(ciphertext, key)
    return cc.CCCrypto:decryptXXTEA(ciphertext, string.len(ciphertext), key, string.len(key))
end

function crypto.encodeBase64(plaintext)
    return cc.CCCrypto:encodeBase64(plaintext, string.len(plaintext))
end

function crypto.decodeBase64(ciphertext)
    return cc.CCCrypto:decodeBase64(ciphertext)
end

function crypto.md5(input, isRawOutput)
    if type(isRawOutput) ~= "boolean" then isRawOutput = false end
    return cc.CCCrypto:MD5(input, isRawOutput)
end

return crypto
