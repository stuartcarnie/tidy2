var tidyString = require ("./tidy").tidyString;
for (var i=0; i<1000000; i++) {
    var result = tidyString("<html><head><title>I am title</head><body><p>this is body</p></body></html>");
    if (i % 10000 === 0) {
        console.log("iterations: " + i);
    }
}
