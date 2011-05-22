 #include "ptable.h"
 #include "system.h"
 
  // Khởi tạo size đối tuong pcb để luu size process. Gán giá trị ban đầu là null. Nhớ khởi tạo *bm và *bmsem để sử dụng
 PTable::PTable(int size)
 {
	printf ("\n--> Khoi tao ptable");
	 bm = new BitMap (size);
	 for (int i = 0; i<MAXPROCESS; i++)
		 pcb[i] = NULL;
	 psize = size;
	 bmsem = new Semaphore ("bmsem", 1);
	 bm->Mark(0);
	 pcb[0] = new PCB(0);
	 pcb[0]->filename = "./test/shell";
	 pcb[0]->parentID = -1;
	 printf ("\n--> End Khoi tao ptable");
 }
 // hủy các đối tuợng đã tạo
 PTable::~PTable()
 {
	 printf ("\n--> Huy ptable");
	 if( bm != NULL )
		 delete bm;
	 for( int i = 0; i < psize ; ++i){
		 if(pcb[i] != NULL)
			 delete pcb[i];
	 }			
	 if( bmsem != NULL)
		 delete bmsem;	 
 }
 
 //Thực thi cho system call SC_EXEC, Kiểm tra chuong trình đuợc gọi có tồn tại
 // 	 trong máy không. Kiểm tra thử xem chuong trình đuợc gọi là chính nó không?
 // 	 Chúng ta không cho phép điều này. Kiểm tra còn slot trống để luu tiến trình mới
 // 	 không (max là 10 process). Nếu thỏa các điều kiện trên thì ta lấy index của slot
 // 	 trống là ProcessID của tiến trình mới tạo này, giả sử là ID. Và gọi phuong thức
 // 	 Exec của lớp PCB với đối tuợng tuong ứng quản ly process này, nghĩa là gọi
 // 	 pcb[ID]->Exec(…). Xem chi tiết mô tả lớp PCB ở bên duới.
 // 	 Phuong thức này đuợc gọi trong hàm xử ly system call SC_Exec
 
 int PTable::ExecUpdate(char* name,int _in_priority)// return PID
 {
	 printf ("\n--> Bat dau ExecUpdate");
	 bmsem->P();
	 if(name == NULL)
	 {
		 printf("\nPTable-->Exec : Chuong trinh khong ton tai trong may");
		 bmsem->V();
		 return -1;
	 }
	 //Xuat thong bao loi neu Chuong trinh goi lai chinh no
	 if( strcmp(name,"./test/shell") == 0 )
	 {
		 printf("\nPTable-->Exec :Chuong trinh goi lai chinh no");		
		 bmsem->V();
		 return -1;
	 }
	 if( strcmp(name,currentThread->getName()) == 0 )
	 {
		 printf("\nPTable-->Exec : Chuong trinh goi lai chinh no");		
		 bmsem->V();
		 return -1;
	 }
	 int ID = this->GetFreeSlot();
	 if(ID<0)
	 {
		 printf("\nPTable-->Exec : Khong con slot trong");		
		 bmsem->V();
		 return -1;
	 }
	 pcb[ID] = new PCB(ID);
	 pcb[ID]->filename = new char [strlen(name)]; //luu filename
	 pcb[ID]->filename = name;
	 pcb[ID]->priority =  _in_priority;		//gan do uu tien
	 
	 int pid = pcb[ID]->Exec(name,ID);
	 //NOTE
	 printf("\n*******************End ExecUpdate******************");
	 printf("\ncurrentThread->name = %s",currentThread->getName());
	 printf("\ncurrentThread->ID = %d",currentThread->processID);
	 
	 bmsem->V();
	 return pid;
 }
 
 //Đuợc thủ tục sử ly cho system call SC_Exit sử dụng. Trong system call này
 // 	 chúng ta kiểm tra thử PID có tồn tại không, sau đó chúng ta mới xử ly kết thúc tiến
 // 	 trình, phải gọi JoinRelease() để giải phóng sự chờ đợi của tiến trình cha và
 // 	 ExitWait() để xin phép tiến trình cha cho kết thúc.
 // 	 Chú y là sau khi gọi thủ tục này, chúng ta phải giải phóng tiểu trình hiện tại bằng
 // 	 các dòng lênh nhu sau, nếu là main process thì chúng ta gọi hàm Halt() luôn
 // 	 
 // 	 int pid = currentThread->processID;
 // 	 currentThread->FreeSpace();
 // 	 if(pid == 0){//exit main process
 // 		interrupt->Halt();
 // 	 }
 // 	 currentThread->Finish();
 int PTable::ExitUpdate(int ec)
 {
	 printf ("\n--> Bat dau ExitUpdate");
	 int id = currentThread->processID;
	 if(id == 0)
	 {
		 interrupt->Halt();
		 return -1;
	 }
	 if (IsExist(id) == false)
	 {
		 printf("\nPTable-->ExitUpdate : PID %d khong ton tai ",id);
		 return -1;
	 }
	 pcb[id]->SetExitCode(ec);
	 pcb[pcb[id]->parentID]->DecNumWait();
	 
	 pcb[id]->JoinRelease();
	 pcb[id]->ExitWait();
	 Remove(id);
	 printf ("\n--> Ket Thuc ExitUpdate");
	 return ec;
	 
 }
 
 // Đuợc sử dụng khi mà chúng ta viết thủ tục cho system call Join(), trong thủ tục
 // 	 này thì tiến trình cha gọi pcb[id]->JoinWait() để chờ cho tới khi tiến trình con kết
 // 	 thúc (truớc khi tiến trình con kết thúc thì tiến trình con gọi JoinRelease()). Sau đó
 // 	 tiến trình cha lại gọi ExitRelease() để cho phép tiến trình con đuợc kết thúc.
 // 	 Chú y là chúng ta không cho phép tiến trình join vào chính nó, hoặc là join vào
 // 	 tiến trình khác không phải là cha của nó.
 int PTable::JoinUpdate(int id)
 {
	 printf ("\n--> Bat dau JoinUpdate");
	 if (id < 0)
	 {
		 printf("\nPTable-->JoinUpdate : PID %d khong ton tai ",id);
		 return -1;
	 }
	 if (currentThread->processID != pcb[id]->parentID)
	 {
		 printf("\nPTable-->JoinUpdate : Join vao tien trinh khac khong phai la cha no");
		 return -1;
	 }
	 pcb[pcb[id]->parentID]->IncNumWait();
	 pcb[id]->JoinWait();
	 
	 int ec = pcb[id]->GetExitCode();
	 pcb[id]->ExitRelease();
	 printf ("\n--> Ket thuc JoinUpdate");
	 return ec;
 }
 
 int PTable::GetFreeSlot()
 {
	 return bm->Find();
 }
 //Tìm free slot để luu thông tin cho tiến trình mới
 bool PTable::IsExist(int pid)
 {
	 return bm->Test(pid);
 }
 //kiểm tra có tồn tại process ID này không
 void PTable::Remove(int pid)
 {
	 bm->Clear(pid);
	 if(pcb[pid] != NULL)
		 delete pcb[pid];
 }
 //Xóa một processID ra khỏi mãng quản ly nó, khi mà tiến trình này đã kết thúc
 
 
 
 