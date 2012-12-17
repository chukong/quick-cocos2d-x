
__FRAMEWORK_ENVIRONMENT__ = "server"

require("framework.shared.debug")
require("framework.shared.functions")

json = require("framework.shared.json")

REQUEST_METHOD = ngx.req.get_method()
GET = ngx.req.get_uri_args()
if REQUEST_METHOD == "POST" then
    -- ngx.req.read_body()
    POST = ngx.req.get_post_args()
else
    POST = {}
end

-- function app:error(reason, errorMessage, moduleName)
--     if not moduleName then moduleName = app.currentActionModuleName end

--     if HTML_DEBUG_OUTPUT then
--         echo("<p><strong>ERROR: " .. string.upper(reason) .. "</strong></p>")
--         if moduleName then
--             echo("<p><strong>MODULE</strong>: " .. moduleName .. "</p>")
--         end
--         echo("<p><strong>MESSAGE:</strong></p>")
--         echo("<pre>")
--         echo(string.text2html(errorMessage))
--         echo("</pre>")
--         echo("<p><strong>DEBUG STACK TRACEBACK:</strong></p>")
--         echo("<pre>")
--         local trace = debug.traceback("", 2)
--         trace = string.split(trace, "\n")
--         table.remove(trace, 1)
--         for i, line in ipairs(trace) do
--             line = string.ltrim(line)
--             echo(string.text2html(string.format("    %d: %s", #trace - i + 1, line)))
--         end
--         echo("</pre>")
--     else
--         echo("")
--         echo("")
--         echo("## ERROR: " .. string.upper(reason))
--         if moduleName then
--             echo("## MODULE: " .. moduleName)
--         end
--         echo("## MESSAGE:")
--         echo("")
--         echo(errorMessage)
--         echo("")
--         echo("## DEBUG STACK TRACEBACK:")
--         echo("")
--         local trace = debug.traceback("", 2)
--         trace = string.split(trace, "\n")
--         table.remove(trace, 1)
--         for i, line in ipairs(trace) do
--             line = string.ltrim(line)
--             echo(string.format("    %d: %s", #trace - i + 1, line))
--         end
--         echo("")
--         echo("")
--     end
--     ngx.exit(ngx.HTTP_OK)
-- end
