document.getElementById("login-submit-button").addEventListener("click", checkLoginInfo)
var loginForm = document.forms["login-form"]


function checkLoginInfo()
{
    var list = fetchJSON("userlist.json")
    // console.log(list)
    JSON.parse(list)
    // console.log(list)
    for (var i = 0; i < list.list.length; i++)
    {
        if (loginForm["uname"].value == list.list[i].uname)
        {
            if (loginForm["psw"].value == list.list[i].password)
            {
                console.log("SUCCESS!")
            }
        }
    }
    
}