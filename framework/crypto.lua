--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--[[--

加解密、数据编码

]]
local crypto = {}

--[[--

使用 AES256 算法加密内容

提示：AES256 仅在 iOS 和 Mac 平台可用。加解密尽量选择跨平台的 XXTEA 接口。

@param string plaintext 明文字符串
@param string key 密钥字符串

@return string  加密后的字符串

]]
function crypto.encryptAES256(plaintext, key)
    plaintext = tostring(plaintext)
    key = tostring(key)
    return CCCrypto:encryptAES256(plaintext, string.len(plaintext), key, string.len(key))
end

--[[--

使用 AES256 算法解密内容

提示： AES256 仅在 iOS 和 Mac 平台可用。加解密尽量选择跨平台的 XXTEA 接口。

@param string ciphertext 加密后的字符串
@param string key 密钥字符串

@return string  明文字符串

]]
function crypto.decryptAES256(ciphertext, key)
    ciphertext = tostring(ciphertext)
    key = tostring(key)
    return CCCrypto:decryptAES256(ciphertext, string.len(ciphertext), key, string.len(key))
end

--[[--

使用 XXTEA 算法加密内容

@param string plaintext 明文字符串
@param string key 密钥字符串

@return string  加密后的字符串

]]
function crypto.encryptXXTEA(plaintext, key)
    plaintext = tostring(plaintext)
    key = tostring(key)
    return CCCrypto:encryptXXTEA(plaintext, string.len(plaintext), key, string.len(key))
end

--[[--

使用 XXTEA 算法解密内容

@param string ciphertext 加密后的字符串
@param string key 密钥字符串

@return string  明文字符串

]]
function crypto.decryptXXTEA(ciphertext, key)
    ciphertext = tostring(ciphertext)
    key = tostring(key)
    return CCCrypto:decryptXXTEA(ciphertext, string.len(ciphertext), key, string.len(key))
end

--[[--

使用 BASE64 算法编码内容

@param string plaintext 原文字符串

@return string  编码后的字符串

]]
function crypto.encodeBase64(plaintext)
    plaintext = tostring(plaintext)
    return CCCrypto:encodeBase64(plaintext, string.len(plaintext))
end

--[[--

使用 BASE64 算法解码内容

@param string ciphertext 编码后的字符串

@return string  原文字符串

]]
function crypto.decodeBase64(ciphertext)
    ciphertext = tostring(ciphertext)
    return CCCrypto:decodeBase64(ciphertext)
end

--[[--

计算内容的 MD5 码

@param string input 内容字符串
@param boolean isRawOutput 是否返回二进制 MD5 码

@return string MD5 字符串

]]
function crypto.md5(input, isRawOutput)
    input = tostring(input)
    if type(isRawOutput) ~= "boolean" then isRawOutput = false end
    return CCCrypto:MD5(input, isRawOutput)
end

--[[--

计算文件的 MD5 码

@param string path 文件路径

@return string MD5 字符串

]]
function crypto.md5file(path)
    if not path then
        printError("crypto.md5file() - invalid filename")
        return nil
    end
    path = tostring(path)
    if DEBUG > 1 then
        printInfo("crypto.md5file() - filename: %s", path)
    end
    return CCCrypto:MD5File(path)
end

return crypto
