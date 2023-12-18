UC6_DeleteFlight()
{
	int flight_id_num = 0;	  	
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
	
	web_reg_find("Text/IC=Web Tours",LAST);
	
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
	
	web_reg_find("Text=User wants the intineraries",LAST);	

	web_reg_save_param("flight_id",
				"LB=name=\"flightID\" value=\"",
				"RB=\"",
				"Ord=ALL",
				LAST);

	web_url("Itinerary Button",
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=itinerary",
		"TargetFrame=body",
		"Resource=0",
		"RecContentType=text/html",
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home",
		"Snapshot=t3.inf",
		"Mode=HTML",
		LAST);
	
	flight_id_num = atoi(lr_eval_string("{flight_id_count}"));
	flight1_before_delete = atoi(lr_eval_string("{flight_id_1}"));

	lr_end_transaction("AllBookings",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("Delete Flight");
	
	web_reg_save_param("flights_numbers",
				"LB=<b>A total of ",
				"RB= scheduled flights.</font></b>",
				LAST);
	
	web_reg_save_param("flight_id_after",
				"LB=name=\"flightID\" value=\"",
				"RB=\"",
				"Ord=ALL",
				LAST);
	
	if (atoi(lr_eval_string("{delete_num}")) == 1){
				
				web_submit_form("web_submit_form",
					ITEMDATA,
					"Name=1", "Value=on", ENDITEM,
					"Name=removeFlights.x", "Value=33", ENDITEM,
					"Name=removeFlights.y", "Value=4", ENDITEM,
					EXTRARES,
					"URL=http://localhost:1080/cgi-bin/itinerary.pl",
					"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
					LAST);
			
			} else if (atoi(lr_eval_string("{delete_num}")) == 2){
				
				web_submit_form("web_submit_form",
					ITEMDATA,
					"Name=1", "Value=on", ENDITEM,
					"Name=2", "Value=on", ENDITEM,
					"Name=removeFlights.x", "Value=33", ENDITEM,
					"Name=removeFlights.y", "Value=4", ENDITEM,
					EXTRARES,
					"URL=http://localhost:1080/cgi-bin/itinerary.pl",
					"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
					LAST);
			
			} else if (atoi(lr_eval_string("{delete_num}")) == 3){
				
				web_submit_form("web_submit_form",
					ITEMDATA,
					"Name=1", "Value=on", ENDITEM,
					"Name=2", "Value=on", ENDITEM,
					"Name=3", "Value=on", ENDITEM,
					"Name=removeFlights.x", "Value=33", ENDITEM,
					"Name=removeFlights.y", "Value=4", ENDITEM,
					EXTRARES,
					"URL=http://localhost:1080/cgi-bin/itinerary.pl",
					"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
					LAST);
			
			}
	
	 		flight1_after_delete = atoi(lr_eval_string("{flight_id_after_1}"));
	 		
	 		if (flight1_before_delete == flight1_after_delete){

				lr_error_message("Itinerary not deleted");	
	
			} else if (flight1_before_delete == flight1_after_delete){

			lr_output_message( "The itinerary was deleted #%s", lr_eval_string("{flight1_before_delete}"));

			}
	 		
	
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