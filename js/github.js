var request = new XMLHttpRequest();

request.open('get', 'https://api.github.com/repos/incomingstick/openrpg/tags', true);
request.onload = () => {
    var response = JSON.parse(request.responseText);

    response.forEach(tag => {
        // TODO build the release chart
        console.log(tag.name);
    });
};

request.send();