
CREATE TABLE Person(
	UserID		Char(9) PRIMARY KEY,
	Address	CHAR(100) NOT NULL,		# Employee Address
	PhoneNumber	CHAR(12) NOT NULL,		# Phone Number of employee
	Email		CHAR(30) NOT NULL,		# Email of employee
	Name		CHAR(50) NOT NULL		# Name of employee
);

CREATE TABLE Client(
	UserID		CHAR(9)  NOT NULL,		# UserID is the primary key
	
	PRIMARY KEY (UserID),
	FOREIGN KEY (UserID) REFERENCES Person(UserID)	
);

CREATE TABLE Employee(
	UserID		CHAR(9)  NOT NULL,		# UserID is the primary key and is the user id of the employee
	JobTitle	CHAR(20) NOT NULL,		# Job title of the employee
	Specialty	Char(20) NOT NULL,		# Specialty of the employee
	PayRate	DECIMAL(12.2) NOT NULL,	# Hourly pay

	PRIMARY KEY (UserID),
	FOREIGN KEY (UserID) REFERENCES Person(UserID)	
);

CREATE TABLE Service(
	ServiceType	CHAR(9) PRIMARY KEY,		# Service type is the primary key
	Cost		DECIMAL(12.2)			# Cost of the service
);

CREATE TABLE Appointment(
	AppointmentID	CHAR(9) PRIMARY KEY,		# The AppointmentID is the primary key
	ClientID	CHAR(9) NOT NULL,		# ClientID is the UserID foreign key of the client
	EmployeeID	CHAR(9) NOT NULL,		# EmployeeID is the UserID foreign key of the employee that was assigned to the appointment
	ServiceType	CHAR(9) NOT NULL,		# The type of service that the appointment is handling
	PreferredEmp	CHAR(9) NULL,			# PreferredEmp is the preferred employee that the user may have selected
	Date		TIMESTAMP NOT NULL,		# The date of the appointment
	
	FOREIGN KEY (ClientID) REFERENCES Client(UserID),
	FOREIGN KEY (EmployeeID) REFERENCES Employee(UserID),
	FOREIGN KEY (ServiceType) REFERENCES Service(ServiceType)
);

CREATE TABLE Bill(
	AppointmentID	CHAR(9) NOT NULL,		# The AppointmentID is the primary key and correlates the specific bill with the appointment
	ClientID	CHAR(9) NOT NULL,		# The ClientID is the UserID of the client that the bill is for
	Amount		DECIMAL(12.2) NOT NULL,	# The amount that the client owes
	IsPayed	CHAR(1) NOT NULL,		# Whether or not this bill was paid
	Date		TIMESTAMP NOT NULL,		# The date of the bill that was issued
	
	PRIMARY KEY (AppointmentID),
	FOREIGN KEY (AppointmentID) REFERENCES Appointment(AppointmentID),
	FOREIGN KEY (ClientID) REFERENCES Client(UserID)
);