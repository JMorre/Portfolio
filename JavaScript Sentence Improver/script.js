const dkey = "ae04c5f5-ab5b-46a9-af22-6414f9e06652";
const tkey = "10dcbfe0-3746-4744-a71c-1dbba286b2d7";

var parsesyn = function(s) {
  var pos = 0;
  var pos0 = 0;
  pos0 = s.indexOf("\"syns\":");
  pos = pos0 + 10;
  pos0 = s.indexOf("\"", pos);
  var ret = s.substring(pos, pos0);
  return ret;
}

var parseant = function(s) {
  var pos = 0;
  var pos0 = 0;
  pos0 = s.indexOf("\"ants\":");
  pos = pos0 + 10;
  pos0 = s.indexOf("\"", pos);
  return s.substring(pos, pos0);
}

var parsesame = function(s) {
  var pos = 0;
  var pos0 = 0;
  pos0 = s.indexOf("\"id\":");
  pos = pos0 + 6;
  pos0 = s.indexOf("\"", pos);
  return s.substring(pos, pos0);
}

var nextskip = function(s, i) {
  while (!isskip(s, i)) {
    i++;
    if (i >= s.length) {
      return -1;
    }
  }
  return i;
}

var nextletter = function(s, i) {
  while (isskip(s, i)) {
    i++;
    if (i >= s.length) {
      return -1;
    }
  }
  return i;
}

var isskip = function(s, i) {
  var patt = new RegExp(/[A-Za-z]/);
  if (patt.test(s[i])) {
    return false;
  } else {
    return true;
  }
}

var addstrings = function(values1, s, ss, i, ivalue) {
  var ret = "";
  if (i === 0) {
    ret += ivalue.substring(i, values1[i][1]);
  }
  else {
    ret += ivalue.substring(values1[i - 1][2], values1[i][1]);
  }
  ret += s;
  return ret;
}

var addstringa = function(values1, a, sa, i, ivalue) {
  var ret = "";
  if (i === 0) {
    ret += ivalue.substring(i, values1[i][1]);
  }
  else {
    ret += ivalue.substring(values1[i - 1][2], values1[i][1]);
  }
  ret += a;
  return ret;
}

var sorta = function(strings) {
  for (let i = 0; i < strings.length; i++) {
    var maxind = i;
    var max = strings[i];
    for (let j = 0 + i; j < strings.length; j++) {
      if (strings[j][1] > max[1]) {
        max = strings[j];
        maxind = j;
      }
    }
    strings[maxind] = strings[i];
    strings[i] = max;
  }
  return strings;
}

var laststrings = function(values1, ivalue) {
  var pos0 = values1[values1.length - 1][2];
  var pos = ivalue.length;
  return ivalue.substring(pos0, pos);
}

document.getElementById("UserSubmit").addEventListener("click", function(event) {
  event.preventDefault();
  const ivalue = document.getElementById("UserInput").value;
  if (ivalue === "") {
    return;
  }
  var value = [];
  var pos0 = 0;
  var pos = 0;

  while (pos !== -1) {
    pos0 = nextletter(ivalue, pos);
    if (pos0 === -1) {
      break;
    }
    pos = nextskip(ivalue, pos0);
    if (pos === -1) {
      value.push([ivalue.substring(pos0, ivalue.length), pos0, ivalue.length]);
    } else {
      value.push([ivalue.substring(pos0, pos), pos0, pos]);
    }
  }
  var ss = "";
  var sa = "";
  var strings = [];
  var stringa = [];
  var n = 0;
  for (let i = 0; i < value.length; i++) {
    const url = "https://dictionaryapi.com/api/v3/references/thesaurus/json/" + value[i][0] + "?key=" + tkey;
    fetch(url, values = value)
      .then(function(response) {
        return response.json();
      }).then(function(json, values1 = values) {
        console.log(JSON.stringify(json));
        var ret = [];
        let test = parsesame(JSON.stringify(json));
        let s = "";
        let a = "";
        if (values1[i][0] !== test) {
          s = values1[i][0];
          a = values1[i][0];
        }
        else {
          s = parsesyn(JSON.stringify(json));
          a = parseant(JSON.stringify(json));
        }
        if (a === "") {
          a = parsesame(JSON.stringify(json));
        }
        ss = addstrings(values1, s, ss, i, ivalue);
        sa = addstringa(values1, a, ss, i, ivalue);

        strings.push([ss, i]);
        stringa.push([sa, i]);
        n++;
        if (n === values1.length) {
          //push the last non-word values to strings/stirnga
          strings.push([laststrings(values1, ivalue), n]);
          stringa.push([laststrings(values1, ivalue), n]);
          var final = "<h2>This means exactly the same thing:</h2><p>";
          strings = sorta(strings);
          stringa = sorta(stringa);
          for (var k = strings.length - 1; k >= 0; k--) {
            final += strings[k][0];
          }
          final += "</p><br><h2>This means exactly the opposite:</h2><p>";
          for (var k = stringa.length - 1; k >= 0; k--) {
            final += stringa[k][0];
          }
          final += "</p>";
          document.getElementById("Output").innerHTML = final;
        }
      });
  }
  console.log(ss)
});
