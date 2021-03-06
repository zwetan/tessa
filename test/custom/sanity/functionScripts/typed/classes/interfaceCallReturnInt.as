package richards {
    var COUNT:int = 1000;

    runRichards();

    public function runRichards():void {
        var scheduler:Scheduler = new Scheduler();

        var queue:Packet = new Packet(null, ID_WORKER, KIND_WORK);
        queue = new Packet(queue,  ID_WORKER, KIND_WORK);
        scheduler.addHandlerTask(ID_HANDLER_A, 2000, queue);
        scheduler.schedule();
    }

    const ID_IDLE:int       = 0;
    const ID_WORKER:int     = 1;
    const ID_HANDLER_A:int  = 2;
    const ID_HANDLER_B:int  = 3;
    const ID_DEVICE_A:int   = 4;
    const ID_DEVICE_B:int   = 5;
    const NUMBER_OF_IDS:int = 6;

    const KIND_DEVICE:int   = 0;
    const KIND_WORK:int     = 1;

    public class Scheduler {
        public var queueCount:int;
        public var holdCount:int;
        public var list:TaskControlBlock;
        public var currentTcb:TaskControlBlock;
        public var currentId:int;

        public function Scheduler() {
            this.queueCount = 0;
            this.holdCount = 0;
            this.list = null;
            this.currentTcb = null;
            this.currentId = null;
            print("Created scheduler");
        }

        public function addHandlerTask(id:int, priority:int, queue:Packet):void {
            this.addTask(id, priority, queue, new HandlerTask(this));
        };


        public function addTask(id:int, priority:int, queue:Packet, task:Task):void {
            this.currentTcb = new TaskControlBlock(this.list, id, priority, queue, task);
            this.list = this.currentTcb;
        };

        public function schedule():void {
            this.currentTcb = this.list;
				print("Scheduling tcb: " + currentTcb);
				if (this.currentTcb.isHeldOrSuspended()) {
					print("Freedom");
				} else {
					print("Running interface");
					this.currentId = this.currentTcb.id;
                    var result:int = this.currentTcb.run();
					print("Interface result : " + result);
                }
        };

        public function holdCurrent():TaskControlBlock {
            this.holdCount++;
            this.currentTcb.markAsHeld();
            return this.currentTcb.link;
        };

        public function suspendCurrent():TaskControlBlock {
            this.currentTcb.markAsSuspended();
            return this.currentTcb;
        };
    }

    public class TaskControlBlock {
        public var link:TaskControlBlock;
        public var id:int;
        public var priority:int;
        public var queue:Packet;
        public var task:Task;
        public var state:int;
  
        public function TaskControlBlock(link:TaskControlBlock, id:int, priority:int, queue:Packet, task:Task):void {
            this.link = link;
            this.id = id;
            this.priority = priority;
            this.queue = queue;
            this.task = task;
            if (queue == null) {
                this.state = STATE_SUSPENDED;
            } else {
                this.state = STATE_SUSPENDED_RUNNABLE;
            }
        }

        const STATE_RUNNING:int = 0;
        const STATE_RUNNABLE:int = 1;
        const STATE_SUSPENDED:int = 2;
        const STATE_HELD:int = 4;
        const STATE_SUSPENDED_RUNNABLE:int = STATE_SUSPENDED | STATE_RUNNABLE;
        const STATE_NOT_HELD:int = ~STATE_HELD;

        public function setRunning():void {
            this.state = STATE_RUNNING;
        };

        public function markAsNotHeld():void {
            this.state = this.state & STATE_NOT_HELD;
        };

        public function markAsHeld():void {
            this.state = this.state | STATE_HELD;
        };

        public function isHeldOrSuspended():Boolean {
            return (this.state & STATE_HELD) != 0 || (this.state == STATE_SUSPENDED);
        };

        public function markAsSuspended():void {
            this.state = this.state | STATE_SUSPENDED;
        };

        public function markAsRunnable():void {
            this.state = this.state | STATE_RUNNABLE;
        };

        public function run():int{
            print(this.task);
            var resultingTask:int = this.task.run(5);
            print("Resulting task in schedule " + resultingTask);
            return 20;
        };

    } // class TaskControlBlock

    public interface Task {
        function run(x:int):int;
    } // interface Task

    public class HandlerTask implements Task {
        private var scheduler:Scheduler;

        public function HandlerTask(scheduler:Scheduler):void {
            this.scheduler = scheduler;
        }

        public function run(x:int):int{
			print("Running handler task");
            return 10;
        };

    } // class HandlerTask

    const DATA_SIZE:int = 4;
    public class Packet {
        public var link:Packet;
        public var id:int;
        public var kind:int; 
        public var a1:int;

        public function Packet(link:Packet, id:int, kind:int):void {
            this.link = link;
            this.id = id;
            this.kind = kind;
            this.a1 = 0;
        }

        public function toString():String {
            return "Packet";
        };
    } // class Packet

}
