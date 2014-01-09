local _p = {
send = {
    [1000] = {
        [0] = {
            ["keys"] = {"uid",},
            ["fmt"] = "R",
            },

        },
    },
receive = {
    [2000] = {
        [0] = {
            ["keys"] = {"uid","code","ip","port",},
            ["fmt"] = "RRSR",
            },

        },
    },
}
return _p
