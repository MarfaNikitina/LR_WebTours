Action1()
{

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_cookie("csrftoken=Pu1k109gOPWuGFN6iUUFJu41ZueeAvRA0cm8ZuPYBWoIXc2NH7hGZTrBoadTWaBz; DOMAIN=127.0.0.1");

	web_url("welcome.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	web_url("login.pl", 
		"URL=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/WebTours/home.html", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		LAST);

	lr_think_time(42);

	web_submit_data("login.pl_2", 
		"Action=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=Banana", ENDITEM, 
		"Name=password", "Value=banana", ENDITEM, 
		"Name=passwordConfirm", "Value=banana", ENDITEM, 
		"Name=firstName", "Value=Banana", ENDITEM, 
		"Name=lastName", "Value=Banana", ENDITEM, 
		"Name=address1", "Value=Banana street", ENDITEM, 
		"Name=address2", "Value=Banana town", ENDITEM, 
		"Name=register.x", "Value=58", ENDITEM, 
		"Name=register.y", "Value=12", ENDITEM, 
		LAST);

	lr_think_time(6);

	web_url("button_next.gif", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/login.pl", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	lr_think_time(6);

	web_url("SignOff Button", 
		"URL=http://127.0.0.1:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://127.0.0.1:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	return 0;
}