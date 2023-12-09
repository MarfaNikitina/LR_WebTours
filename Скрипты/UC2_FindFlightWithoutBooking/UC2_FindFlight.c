UC2_FindFlight()
{
	lr_start_transaction("FindFlightWithoutBooking");

	lr_start_transaction("StartPage");
	
	web_reg_save_param("userSession",
	                   "LB=userSession\" value=\"",
	                   "RB=\"",
	                   LAST);
	                   
	web_reg_find("Text/IC=Web Tours",LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("StartPage",LR_AUTO);

	lr_think_time(12);

	lr_start_transaction("Login");
	
	web_reg_find("Text/IC=User password was correct",LAST);
	 
	web_submit_data("login.pl",
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={username}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=49", ENDITEM,
		"Name=login.y", "Value=1", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(6);

	lr_start_transaction("Flights");
	
	web_reg_find("Text/IC= User has returned to the search page",LAST);

/*Correlation comment - Do not change!  Original value='12/04/2023' Name ='departDate' Type ='RecordReplay'*/
	web_reg_save_param_attrib(
		"ParamName=departDate",
		"TagName=input",
		"Extract=value",
		"Name=returnDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);

	web_url("Search Flights Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Flights",LR_AUTO);

	lr_think_time(5);


/*Correlation comment - Do not change!  Original value='010;386;12/03/2023' Name ='outboundFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
	
	lr_start_transaction("FindFlight");
	
	web_reg_find("Text/IC= from <B>{departCity}</B> to <B>{arrivalCity}</B> ",LAST);

	web_submit_data("reservations.pl",
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl?page=welcome",
		"Snapshot=t4.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=depart", "Value={departCity}", ENDITEM,
		"Name=departDate", "Value={departDate}", ENDITEM,
		"Name=arrive", "Value={arrivalCity}", ENDITEM,
		"Name=returnDate", "Value={returnDate}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=findFlights.x", "Value=65", ENDITEM,
		"Name=findFlights.y", "Value=6", ENDITEM,
		"Name=.cgifields", "Value=roundtrip", ENDITEM,
		"Name=.cgifields", "Value=seatType", ENDITEM,
		"Name=.cgifields", "Value=seatPref", ENDITEM,
		LAST);
	
	lr_end_transaction("FindFlight", LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("ChooseFlight");
	
	web_reg_find("Text/IC=Flight Reservation",LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=46", ENDITEM, 
		"Name=reserveFlights.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("ChooseFlight",LR_AUTO);

	lr_think_time(6);

	lr_start_transaction("Logout");
	
	web_reg_find("Text/IC=Web Tours",LAST);

	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	
	lr_end_transaction("FindFlightWithoutBooking", LR_AUTO);

	return 0;
}