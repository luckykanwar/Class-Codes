create table customers (
   username   varchar(10) primary key,
   password   varchar(32),
   address    varchar(100),
   phone	  varchar(20),
   email      varchar(45)
);

create table shoppingbasket (
   basketId   varchar(13) primary key,
   username	  varchar(10) references Customers (username)
);

create table author(
	ssn varchar(20),
	name varchar(100), 
	address    varchar(100),
	phone	  varchar(20)
);


create table stocks(
	isbn varchar(20) references book(isbn),
	warehousecode varchar(20) references warehouse(warehousecode),
	number integer,
	primary key (isbn,warehousecode) 
);

create table contains(
	isbn varchar(20) references book(isbn), 
	
);
