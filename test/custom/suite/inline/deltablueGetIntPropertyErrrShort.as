package deltablue {

public class OrderedCollection {
    private var elms:Array;
    
    public function OrderedCollection() {
        this.elms = new Array();
    }
    
    public function add(elm):void {
		print("Length: " + " other sthtuff"); 
		print("Length: " + "Length: "); 
		print("Finished add");
        elms[elms.length] = elm;
		//print("Length: " + "Length: "); 
		//print("Finished adding constraint");
    }
    
    public function at(index:int):* {
		print("WTF");
		var result = this.elms[index];
		print("already atted");
		return result;
    }
} 


public class Constraint {
    public function Constraint():void {
    }
} 


function chainTest(n:int) {
	var ordered:OrderedCollection = new OrderedCollection();
	var constraint:Constraint = new Constraint();
	ordered.add(constraint);
	print("Atting");
	var retrive:Constraint = ordered.at(0);
	print("Got!");
	
}

chainTest(100);

} // package
