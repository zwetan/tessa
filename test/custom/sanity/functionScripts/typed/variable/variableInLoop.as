function definedLater() {
    var x:int = 10;
    var i:int = 0;

    for (i = 0; i < 10; i++) {
        for (var j:int = 0; j < 10; j++) {
            x++;
        }
    }

    print(x);
    print(j);
}

definedLater();
