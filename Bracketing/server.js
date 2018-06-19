var http = require('http');
var fs = require('fs');
var path = require('path');
var express = require('express');
//var bodyParser = require("body-parser");
var app = express();
var mongodb = require("mongodb");
var staticFiles = express.static(__dirname + "/");
app.use(staticFiles);

var countedClicks = 0;
var db;
var databaseUrl = "mongodb://studentmrcode:mrcode123@ds135963.mlab.com:3"

app.set('view engine', 'ejs');

/*mongodb.MongoClient.connect(databaseUrl, function(error, database) {
	db = database;

	db.collection("records").findOne({
		"_id": "clicks"
	}, function(error, result) {
		clicks = result.clicks;
	});
});*/

/*app.use(bodyParser.urlencoded( {
	extended : false
}));
app.use(bodyParser.json());*/

app.post("/clicks", function (request, response) {
	countedClicks++;
	response.render("index", {clicks: countedClicks});
});

app.get("/clicks", function (request, response) {
	response.send(clicks + "");
});

app.get("/", function (request, response) {
	response.render("index", {clicks: countedClicks});
});

app.listen(3000);




