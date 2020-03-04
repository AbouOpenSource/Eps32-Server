function onButton(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET","on",true);
    xhttp.send();
}

function offButton(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET","off",true);
    xhttp.send();
}


setInterval(function getData(){

    var xhttp = new XMLHttpRequest();
    /**
     * 4 ==> the request is ok
     * 200 ==> the status is ok
     * 2000 ==> for the witing time before refresh 
     * for get more details on this part, let's feel free to tap 'Ajax request XMLHttpRequest' on google.
     */
    xhttp.onreadystatechange = function () {
        if(this.readyState == 4 && this.status == 200){
            document.getElementById("etatVanneAspiration").innerHTML = this.response;
        }

    };

    xhttp.open("GET","lireEtat",true);
    xhttp.send();
},2000);