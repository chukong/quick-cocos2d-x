
local M = {}

function M.encryptAES256(plaintext, key)
    return CCCrypto:encryptAES256Lua(plaintext, string.len(plaintext), key, string.len(key))
end

function M.decryptAES256(ciphertext, key)
    return CCCrypto:decryptAES256Lua(ciphertext, string.len(ciphertext), key, string.len(key))
end

function M.encodeBase64(plaintext)
    return CCCrypto:encodeBase64Lua(plaintext, string.len(plaintext))
end

function M.decodeBase64(ciphertext)
    return CCCrypto:decodeBase64Lua(ciphertext)
end

function M.md5(input, isRawOutput)
    if type(isRawOutput) ~= "boolean" then isRawOutput = false end
    return CCCrypto:MD5Lua(input, string.len(input), isRawOutput)
end

return M
