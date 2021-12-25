CREATE TABLE Ticket(
trainDate date , 
trainId int NOT NULL IDENTITY,
wagonNumber nvarchar(25),
placeNumber nvarchar(25),
takenFromStation nvarchar(25),
buyOrReserve nvarchar(25),
ownerInfo nvarchar(25),
ownerFirstName nvarchar(25),
ownerLastName nvarchar(25),
purchaseDate date,
purchasetime time,
);

Select * from Ticket

CREATE TABLE buyAndReserveTicket(
trainId int NOT NULL IDENTITY,
stationName nvarchar(25),
stationNumber nvarchar(25),
arriveDate date,
arriveTime time,
depDate date,
depTime time,
repeatDays nvarchar(25),
);

Select * from buyAndReserveTicket

CREATE TABLE registeredUsers(
uLog nvarchar(25),
uPass nvarchar(25));

Select * from registeredUsers


CREATE TABLE wagonTrains(
trainId int NOT NULL IDENTITY,
wagonNumber nvarchar(25),
stationNumber nvarchar(25));

Select * from wagonTrains
