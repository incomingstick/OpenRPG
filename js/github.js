let request = new XMLHttpRequest();

request.open('get', 'https://api.github.com/repos/incomingstick/openrpg/tags', true);
request.onload = () => {
    let response = JSON.parse(request.responseText);

    let versionElem = document.getElementById('version');
    if(versionElem !== null) versionElem.innerText = "Version " + response[0].name;

    versionElem = document.getElementById('vbadge');
    if(versionElem !== null) versionElem.src = "https://img.shields.io/badge/version-"+ response[0].name +"-blue.svg"

    versionElem = document.getElementById('dl-version');
    if(versionElem !== null) versionElem.innerHTML = "<strong>OpenRPG " + response[0].name + "</strong> is available for download.";

    let dlList = document.getElementById('lib-downloads');
    if(dlList !== null) {
        response.forEach(tag => {
            let release = document.createElement('div');
            release.id = tag.name;

            let titleSection = document.createElement('div');
            titleSection.id = tag.name + "-title";

            let title = document.createElement('h5');
            title.innerText = "OpenRPG " + tag.name;

            titleSection.appendChild(title);

            if(dlList.innerHTML === "") {
                let latestMessage = document.createElement('h6');
                latestMessage.innerText = tag.name + " is the latest release of the OpenRPG library.";

                titleSection.appendChild(latestMessage);
            }

            release.appendChild(titleSection);

            dlList.appendChild(release);
        });
    }
};

request.send();