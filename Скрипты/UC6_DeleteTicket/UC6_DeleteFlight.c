UC6_DeleteFlight()
{
	int ticket_count = 0;	  	
	int flight1_before_delete;
	int flight1_after_delete;
	
	lr_start_transaction("UC6_DeleteBookingScenario");

	lr_start_transaction("StartPage");
//	web_set_sockets_option("SSL_VERSION", "AUTO");
//		
			web_add_auto_header("Sec-Fetch-Site", 
				"none");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"document");
		
			web_add_auto_header("Sec-Fetch-Mode", 
				"navigate");
		
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
	
	web_reg_find("Text/IC=Welcome to the Web Tours site.",LAST);
	
	web_reg_save_param("userSession",
	                   "LB=userSession\" value=\"",
	                   "RB=\"",
	                   LAST);

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

	lr_think_time(5);

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
		"Name=login.x", "Value=44", ENDITEM, 
		"Name=login.y", "Value=16", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("AllBookings");
	
	web_reg_find("Text=Since user has already logged on",
		LAST);
	
	web_reg_save_param_regexp(
		"ParamName=flight_id",
		"RegExp=name\=\"flightID\" value\=\(.*?)\/>",
		"Ordinal=1",
		LAST);
	
//	web_reg_find("Text=Invoice sent to:", "SaveCount=Tickets_Count", LAST);
	
//	/*Correlation comment - Do not change!  Original value='860820-780-qq' Name ='flightID' Type ='ResponseBased'*/
//	web_reg_save_param_attrib(
//		"ParamName=flight_id",
//		"TagName=input",
//		"Extract=value",
//		"Name=flightID",
//		"Type=hidden",
//		"NotFound=WARNING",
//		SEARCH_FILTERS,
//		"IgnoreRedirections=No",
//		"RequestUrl=*/itinerary.pl*",
//		LAST);
	
	
	web_reg_find("Text=User wants the intineraries",LAST);

	web_url("Itinerary Button",
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary",
		"TargetFrame=body",
		"Resource=0",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home",
		"Snapshot=t3.inf",
		"Mode=HTML",
		LAST);

	lr_end_transaction("AllBookings",LR_AUTO);
	
//	ticket_count = atoi(lr_eval_string("{Tickets_Count}"));

	lr_think_time(5);
		
	lr_start_transaction("Delete Flight");	
	
	web_reg_find("Text/IC={flight_id}","Fail=Found", LAST);
	
	web_submit_form("itinerary.pl",
		 "Snapshot=t4.inf",
		 ITEMDATA,
		"Name=1", "Value=on", ENDITEM,
		"Name=removeFlights.x", "Value=56", ENDITEM,
		"Name=removeFlights.y", "Value=9", ENDITEM,
	LAST);
	
	lr_end_transaction("Delete Flight",LR_AUTO);
	

	lr_think_time(5);

	lr_start_transaction("Logout");
	web_reg_find("Text/IC=Web Tours",LAST);

	web_url("welcome.pl_2",
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1",
		"TargetFrame=",
		"Resource=0",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in={page}",
		"Snapshot=t5.inf",
		"Mode=HTML",
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	lr_end_transaction("UC6_DeleteBookingScenario", LR_AUTO);

	return 0;
}