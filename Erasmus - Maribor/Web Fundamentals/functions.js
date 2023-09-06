var cars = [
    ["data/lexus-ls-14041.png.jpeg", "Lexus", "LS", "2019", "2000cc", 132, "data2/lexus2.jpg"],
    ["data/bentley-bentayga-12899.jpg", "Bentley", "Bentayga", "2015", "3000cc", 350, "data2/bentley2.jpg"],
    ["data/audi-q5.jpeg", "Audi", "Q5", "2017", "2200cc", 90, "data2/audi2.jpg"],
    ["data/skoda-kodiaq-13902.jpg", "Skoda", "Kodiaq", "2016", "3800cc", 75, "data2/skoda2.jpg"],
    ["data/land-rover-range-rover.jpeg", "Land Rover", "Range Rover", "2018", "2700cc", 300, "data2/landrover2.jpg"],
    ["data/mitsubishi-montero-13112.png.jpeg", "Mitsubishi", "Montero", "2017", "2650cc", 89, "data2/mitsubishi2.jpg"],
    ["data/lamborghini-urus-14034.png.jpeg", "Lamborghini", "Urus", "2019", "2400cc", 450, "data2/lamborghini2.jpg"],
    ["data/mercedes-benz-g.jpeg", "Mercedes Benz", "G55", "2012", "2150cc", 190, "data2/mercedes2.jpg"],
    ["data/mini-countryman.jpeg", "Mini Cooper", "Countryman", "2013", "1200cc", 50, "data2/minicooper2.jpg"],
    ["data/maruti-suzuki-s-presso-15087.jpg", "Suzuki", "S-Presso", "2019", "3200cc", 180, "data2/suzuki2.jpg"]
]

createGallery(0);
var temp = cars;

function yearComparatorDescending(a, b) {
    if (a[3] > b[3]) return -1;
    if (a[3] < b[3]) return 1;
    else return 0;
}

function yearComparatorAscending(a, b) {
    if (a[3] < b[3]) return -1;
    if (a[3] > b[3]) return 1;
    else return 0;
}

function engineComparatorDescending(a, b) {
    if (a[4] > b[4]) return -1;
    if (a[4] < b[4]) return 1;
    return 0;
}

function engineComparatorAscending(a, b) {
    if (a[4] < b[4]) return -1;
    if (a[4] > b[4]) return 1;
    return 0;
}

function priceComparatorDescending(a, b) {
    if (a[5] > b[5]) return -1;
    if (a[5] < b[5]) return 1;
    return 0;
}

function priceComparatorAscending(a, b) {
    if (a[5] < b[5]) return -1;
    if (a[5] > b[5]) return 1;
    return 0;
}

var num;

function yearDescending() {
    releasingActive();
    cars.sort(yearComparatorDescending);
    createGallery(1);
    //cars = temp;
    var p = document.getElementById("c1");
    p.className = "active";

}

function yearAscending() {
    releasingActive();
    cars.sort(yearComparatorAscending);
    createGallery(1);
    //cars = temp;
    var p = document.getElementById("c0");
    p.className = "active";
}

function engineDescending() {
    releasingActive();
    cars.sort(engineComparatorDescending);
    createGallery(1);
    //cars = temp;
    var p = document.getElementById("c3");
    p.className = "active";
}

function engineAscending() {
    releasingActive();
    cars.sort(engineComparatorAscending);
    createGallery(1);
    //cars = temp;
    var p = document.getElementById("c2");
    p.className = "active";
}

function priceDescending() {
    releasingActive();
    cars.sort(priceComparatorDescending);
    createGallery(1);
    //cars = temp;
    var p = document.getElementById("c5");
    p.className = "active";
}

function priceAscending() {
    releasingActive();
    cars.sort(priceComparatorAscending);
    createGallery(1);
    //cars = temp;
    var p = document.getElementById("c4");
    p.className = "active";
}

function releasingActive() {
    var j;
    for (j = 0; j < 6; j++) {
        var order = j.toString();
        var id = "c" + order;
        var p = document.getElementById(id);
        p.className = "";
    }
}

function deleteFunction(x) {
    var order = x.id;
    var divID = "g" + order[1];
    cars.splice(order[1], 1);
    console.log(cars);

    element = document.getElementById(divID);
    element.parentNode.removeChild(element);

    reCreateGallery();
    // reCreateGallery();

}
var fileId = 0; // used by the addFile() function to keep track of IDs
function addFile(number) {
    // increment fileId to get a unique ID for the new element

    var html = '<a target="_blank" id="" href="">' +
        '<img src="" id="tempImg" class="ad"/>' +
        '  </a>' +
        '<div class="tablebuttons">' +
        '<div>' +
        '  <table class="desc" id="tempTable">' +
        '    <tr>' +
        '    <th>Brand</th>' +
        '    <td> </td>' +
        '  </tr>' +
        '  <tr>' +
        '    <th>Model</th>' +
        '    <td></td>' +
        '  </tr>' +
        '      <tr>' +
        '    <th>Year</th>' +
        '    <td></td>' +
        '  </tr>' +
        '  <tr>' +
        '    <th>Engine</th>' +
        '    <td></td>' +
        '  </tr> ' +
        '    <tr>' +
        '    <th>Price</th>' +
        '    <td></td>' +
        '  </tr> ' +
        '  </table>' +
        '</div>' +
        '<div class="grid">' +
        '<form>' +
        '  <input type="radio" id="radiotemp" onclick="check(this)">' +
        '  <input type="radio" id="tempRadio" onclick="check(this)">' +
        '</form>' +

        '<button id="tempScale" class="buts" onclick="scaleFunction(this)"> Bigger Pic </button>' +
        '<button id="tempButton" class="buts" onclick="deleteFunction(this)"> Exclude Car</button>' +
        '  <a href="about.html"> <button class="offer">  Contact with us for an offer! </button> </a>' +

        '</div>' +
        '</div>';
    // Adds an element to the document
    var p = document.getElementById("container");
    var newElement = document.createElement('div');
    // newElement.setAttribute('id', elementId);
    newElement.innerHTML = html;
    var x = number.toString();
    var gID = "g" + x;
    var pID = "p" + x;
    var tID = "t" + x;
    var bID = "b" + x;
    var sID = "s" + x;
    var rID = "r" + x;
    var r2ID = "u" + x;
    newElement.setAttribute('class', 'gallery');
    newElement.setAttribute('id', gID);

    p.appendChild(newElement);

    var imgElement = document.getElementById("tempImg");
    imgElement.setAttribute('id', pID);
    var tableElement = document.getElementById("tempTable");
    tableElement.setAttribute('id', tID);
    var deleteButton = document.getElementById("tempButton");
    deleteButton.setAttribute('id', bID);
    var scaleButton = document.getElementById("tempScale");
    scaleButton.setAttribute('id', sID);
    scaleButton.setAttribute('value', 0);
    var radioButton = document.getElementById("radiotemp");
    radioButton.setAttribute('id', rID);
    var secondRadio = document.getElementById("tempRadio");
    secondRadio.setAttribute('id', r2ID);
    document.getElementById(r2ID).checked = true;

}

function check(x) {
    control = x.id[0];
    order = x.id[1];
    first = "r" + x.id[1];
    second = "u" + x.id[1];
    radio1 = document.getElementById(first);
    radio2 = document.getElementById(second);
    if (control == "r")
        radio2.checked = false;
    else
        radio1.checked = false;
    order = parseInt(order);
    handler(order, control);

}

function handler(num, control) {
    order = "p" + num.toString();
    if (control != "u")
        document.getElementById(order).src = cars[num][6];
    else
        document.getElementById(order).src = cars[num][0];

}

function scaleFunction(x) {

    var order = "p" + x.id[1];
    var gorder = "g" + x.id[1];

    console.log("xid", x);
    // document.getElementById(order).src ="lexus2.jpg" ;
    if (x.value == 0) {
        x.innerHTML = "Smaller Pic";
        document.getElementById(order).style.width = "710px";
        document.getElementById(order).style.height = "540px";
        x.value = x.value + 1;
    } else {
        x.innerHTML = "Bigger Pic";
        document.getElementById(order).style.width = "400px";
        document.getElementById(order).style.height = "300px";
        x.value = 0;
    }

    // document.getElementById(gorder).width ="56%" ;
}

function createGallery(start) {

    for (var k = 0; k < cars.length; k++) {
        if (start == 0)
            addFile(k);
        num = k;
        var order = num.toString();
        var srcId = "p" + order;
        var aid = "a" + order;
        var tid = "t" + order;

        table = document.getElementById(tid);

        try {
            document.getElementById(srcId).src = cars[k][0];

            // document.getElementById(aid).href = cars[k][0];
            for (var i = 0; i < table.rows.length; i++)
                if (i != 4) {
                    table.rows[i].cells[1].innerHTML = cars[k][i + 1];
                } else {
                    var price = cars[k][i + 1];
                    price = price.toString(10);
                    price = "€ " + price + "," + "000";
                    table.rows[i].cells[1].innerHTML = price;
                }

        } catch {}

    }
}

function reCreateGallery() {
    for (var k = 0; k < cars.length; k++) {
        num = k;
        var order = num.toString();
        var galleryId = "g" + order;
        var gallery = document.getElementById(galleryId);
        if (gallery == null) {
            num = num + 1;
            var order = num.toString();
            var galleryId = "g" + order;
            var buttonId = "b" + order;
            var tableId = "t" + order;
            var imgId = "p" + order;
            var scaleId = "s" + order;
            var firtRadio = "r" + order;
            var secondRadio = "u" + order;

            var gallery = document.getElementById(galleryId);
            var button = document.getElementById(buttonId);
            var table = document.getElementById(tableId);
            var img = document.getElementById(imgId);
            var scale = document.getElementById(scaleId);
            var radio1 = document.getElementById(firtRadio);
            var radio2 = document.getElementById(secondRadio);

            num = num - 1;
            var order = num.toString();
            gallery.id = "g" + order;
            button.id = "b" + order;
            table.id = "t" + order;
            img.id = "p" + order;
            scale.id = "s" + order;
            radio1.id = "r" + order;
            radio2.id = "u" + order;
        }

    }
}