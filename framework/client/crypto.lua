
local crypto = {}

function crypto.encryptAES256(plaintext, key)
    return CCCrypto:encryptAES256Lua(plaintext, string.len(plaintext), key, string.len(key))
end

function crypto.decryptAES256(ciphertext, key)
    return CCCrypto:decryptAES256Lua(ciphertext, string.len(ciphertext), key, string.len(key))
end

function crypto.encodeBase64(plaintext)
    return CCCrypto:encodeBase64Lua(plaintext, string.len(plaintext))
end

function crypto.decodeBase64(ciphertext)
    return CCCrypto:decodeBase64Lua(ciphertext)
end

function crypto.md5(input, isRawOutput)
    if type(isRawOutput) ~= "boolean" then isRawOutput = false end
    return CCCrypto:MD5Lua(input, isRawOutput)
end

return crypto
