var http = require('http');
var fs = require('fs');
var path = require('path');
var express = require('express');
var bodyParser = require("body-parser");
var app = express();
var mongoClient = require("mongodb").mongoClient;

var staticFiles = express.static(__dirname + "/");
app.use(staticFiles);
//middleware to allow client data to be saved to database
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true}));

var countedClicks = 0;

var db;
var databaseUrl = "mongodb://studentmrcode:mrcode123@ds135963.mlab.com:3"
var mongoose = require("mongoose");
//connects to database on default port 27017
mongoose.Promise = global.Promise;mongoose.connect("mongodb://localhost:27017/my_db");
var playerSchema = new mongoose.Schema({
	name: String,
	elo: Number
});
var Player = mongoose.model("Player", playerSchema);

//stores player info to database
app.post("/addPlayer", (req, res) => {
	var playerData = new Player(req.body);
	playerData.save()
	.then(item => {
		res.send("player saved to database");
	})
	.catch(err => {
		res.status(400).send("unable to save to database");
	});
});

app.set('view engine', 'ejs');

//logs player submissions with middleware function
app.use("/createBracket", function(req, res, next){
	console.log("A new challenjour has arrived: " + Date.now());
	next();
});

app.get("/createBracket/:name/:elo([0-9]{4})", function(req, res) {
	res.send("Name: " + req.params.name + " elo: " + req.params.elo);
});

app.post("/clicks", function(req, res){
	countedClicks++;
	res.render("index", {clicks: countedClicks});
});

app.get("/clicks", function(req, res){
	res.send(clicks + "");
});

app.get('/players', function(req, res){
	res.render('players');
});

app.get("/", function(req, res){
	res.render("index", {clicks: countedClicks});
});

//handles invalid elo submissions
app.get("*", function(req, res){
	res.send("Please enter a valid elo");
});

app.listen(3000);




