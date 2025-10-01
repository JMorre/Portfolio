const express = require('express');
const bodyParser = require("body-parser");
const mongoose = require('mongoose');

const multer = require('multer')
const upload = multer({
  dest: './public/posters/',
  limits: {
    fileSize: 10000000
  }
});

const itemSchema = new mongoose.Schema({
  title: String,
  path: String,
  description: String,
});

const Item = mongoose.model('Item', itemSchema);

const app = express();
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: false
}));

app.use(express.static('public'));

app.post('/api/posters', upload.single('poster'), async (req, res) => {
  // Just a safety check
  if (!req.file) {
    return res.sendStatus(400);
  }
  res.send({
    path: "/posters/" + req.file.filename
  });
});

app.post('/api/items', async (req, res) => {
  const item = new Item({
    title: req.body.title,
    path: req.body.path,
    description: req.body.description,
  });
  try {
    await item.save();
    res.send(item);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

app.delete('/api/items/:id', async (req, res) => {
  try {
    let items = await Item.find();
    await Item.deleteOne({ "_id": req.params.id});
    res.send(items);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

app.get('/api/items', async (req, res) => {
  try {
    let items = await Item.find();
    res.send(items);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

app.put('/api/items/:id', async (req, res) => {
  try {
    let item = await Item.findOne({ "_id": req.params.id});
    console.log(req.body.path);
    item.title = req.body.title;
    item.description = req.body.description;
    if (req.body.path !== "") {
      item.path = req.body.path;
    }
    await item.save();
    res.send(item);
  } catch (error) {
    console.log(error);
    res.sendStatus(500);
  }
});

// connect to the database
mongoose.connect('mongodb://localhost:27017/movies', {
  useNewUrlParser: true
});


app.listen(3000, () => console.log('Server listening on port 3000!'));
