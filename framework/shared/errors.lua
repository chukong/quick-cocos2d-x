
ERROR_NETWORK_CONNECTION_FAILURE = 1
ERROR_NETWORK_TIMEOUT            = 2
ERROR_NETWORK_AUTHENTICATION     = 3
ERROR_NETWORK_CANCELLED          = 4
ERROR_NETWORK_UNKNOWN            = 5
ERROR_UNKNOWN                    = 99

ERROR_SERVER_OK                  = 200
ERROR_SERVER_ERROR               = 500
ERROR_SERVER_NOT_IMPLEMENTED     = 501
ERROR_SERVER_BAD_GATEWAY         = 502
ERROR_SERVER_SERVICE_UNAVAILABLE = 503
ERROR_SERVER_GATEWAY_TIMEOUT     = 504
ERROR_SERVER_FORBIDDEN           = 403

ERROR_INVALID_RESULT             = 1001
ERROR_INVALID_PARAMETERS         = 1002
ERROR_SERVER_INVALID_ACTION      = 1003
ERROR_REDIS_FAILED               = 1004
ERROR_INVALID_SESSION_ID         = 1005


function newError(errorCode, errorMessage)
    local err
    if type(errorCode) == "table" then
        err = clone(errorCode)
    else
        err = {
            errorCode    = errorCode,
            errorMessage = errorMessage,
        }
    end

    return err
end

function try(f, catch_f, finally_f)
    local throw_err
    local function catch_err(err)
        if catch_f then
            throw_err = catch_f(err)
        end
    end

    local ok, result = xpcall(f, catch_err)
    if ok then
        if finally_f then finally_f() end
        return result
    elseif throw_err then
        error(throw_err)
    end
end

function throw(msg, code)
    if code then
        error(format("<<%08u>> - %s", toint(code), tostring(msg)), 2)
    else
        error(msg, 2)
    end
end
