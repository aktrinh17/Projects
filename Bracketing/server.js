var http = require('http');
var fs = require('fs');
var path = require('path');
var express = require('express');
var bodyParser = require('body-parser');
var app = express();
var MongoClient = require('mongodb').MongoClient;

var db;
MongoClient.connect('mongodb://localhost:27017/my_db', (err, client) => {
	if(err) return console.log(err);
	db = client.db('playerNames');
});

var dbConn = MongoClient.connect('mongodb://localhost:27017');

var countedClicks = 0; 
var player = 0;
app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static(path.resolve(__dirname, 'public')));

app.set('view engine', 'ejs');

app.post('/clicks', function (req, res) {
	countedClicks++; 
	db.collection('playerNames').save(req.body, (err, res) => {
        if(err) return console.log(err);
    }); 
    console.log('saved'); 
    res.render('index', {clicks: countedClicks});
});

app.get('/createBracket', (req, res) => {
	db.collection('playerNames').find().toArray((err, result) => {
		if(err) return console.log(err);
	res.render('createBracket', {playerNames: result});
});
});

app.get('/', function(req, res) {
		res.render('index', {clicks: countedClicks});
});

//handles invalid elo submissions
app.get('*', function(req, res) {
	res.send('Please enter a valid elo');
});


app.listen(3000);




