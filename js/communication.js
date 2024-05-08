async function postJSON(data, filename) 
{
    var data;
    const myRequest = new Request("data/" + filename, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            "username": "YOUR_USERNAME",
            "password": "YOUR_PASSWORD"
        })
    });
    fetch(myRequest).then((response) => response.text()).then((text) => 
    {
        
    });
}

async function fetchJSON(filename) 
{
    const myRequest = new Request("data/" + filename);
    var data = await fetch(myRequest).then((response) => response.json()).then((json) => 
    {
        data = json
        console.log(data)
    });
    return data
}
