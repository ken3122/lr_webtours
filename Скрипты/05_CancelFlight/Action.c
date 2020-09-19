Action()
{
	int count = 0;
	int count_response = 0;
	int i;
	int random_number;
	
	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_start_transaction("05_CancelFlight");

		lr_start_transaction("connect_to_server");
	
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
			
			web_reg_save_param("userSession",
					"LB=<input type=\"hidden\" name=\"userSession\" value=\"",
					"RB=\"/>",
					"NotFound=ERROR",
					LAST);
		
			web_reg_find("Fail=NotFound",
			"Text= A Session ID has been created and loaded into a cookie called MSO",
			LAST);
	
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours/", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("connect_to_server", LR_AUTO);
	
	
		lr_start_transaction("login");
	
			web_revert_auto_header("Sec-Fetch-User");
		
			web_add_auto_header("Sec-Fetch-Dest", 
				"frame");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Sec-Fetch-Site", 
				"same-origin");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
						"Text=User password was correct",
						LAST);
			
			web_reg_find("Fail=NotFound",
			             "Text=Welcome, <b>{login}</b>",
						LAST);
	
			web_submit_data("login.pl", 
				"Action=http://localhost:1080/cgi-bin/login.pl", 
				"Method=POST", 
				"TargetFrame=body", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home", 
				"Snapshot=t2.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=userSession", "Value={userSession}", ENDITEM, 
				"Name=username", "Value={login}", ENDITEM, 
				"Name=password", "Value={password}", ENDITEM, 
				"Name=login.x", "Value=82", ENDITEM, 
				"Name=login.y", "Value=6", ENDITEM, 
				"Name=JSFormSubmit", "Value=off", ENDITEM, 
				LAST);
		
		lr_end_transaction("login",LR_AUTO);
	
		lr_start_transaction("click_flights");
	
			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
						"Text=</td></tr> <tr><td align=\"left\">Arrival City :</td> <td><select name=\"arrive\" >",
						LAST);
			
			web_url("Search Flights Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("click_flights",LR_AUTO);
	
		lr_start_transaction("click_find_flight");
	
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
			             "Text=Flight departing from <B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>",
						LAST);
			
			web_reg_save_param("outboundFlight",
				"LB=<input type=\"radio\" name=\"outboundFlight\" value=\"",
				"RB=\"",
				"Ord=ALL",
				LAST);

			web_reg_save_param("flight_number",
				"LB=name=\"outboundFlight\" value=\"",
				"RB=;",
				"Ord=ALL",
				LAST);
			
			web_reg_save_param("flight_hour",
				"LB=<td align=\"center\">",
				"RB=m<td align=\"center\">",
				"Ord=ALL",
				LAST);

			web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=42", ENDITEM, 
				"Name=findFlights.y", "Value=13", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);
	
		lr_end_transaction("click_find_flight",LR_AUTO);
		
		lr_start_transaction("click_choose_flight");
		
			random_number = rand() % lr_paramarr_len("outboundFlight") + 1;
			
			lr_save_string(lr_paramarr_idx("outboundFlight", random_number), "outboundFlight_id");
			
			lr_think_time(5);
		
			web_reg_find("Fail=NotFound",
					    "Text=Payment Details",
						LAST);	
		
			web_submit_data("reservations.pl_2", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=outboundFlight", "Value={outboundFlight_id}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=reserveFlights.x", "Value=60", ENDITEM, 
				"Name=reserveFlights.y", "Value=6", ENDITEM, 
				LAST);

		lr_end_transaction("click_choose_flight",LR_AUTO);

		lr_start_transaction("click_book");

			web_revert_auto_header("Sec-Fetch-User");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(5);
		
			lr_param_sprintf("web_string", "%s :  %sm : Flight %s leaves %s  for %s",
			                 lr_eval_string("{departDate}"),
			                 lr_paramarr_idx("flight_hour", random_number),
			                 lr_paramarr_idx("flight_number", random_number),
							 lr_eval_string("{depart}"),
							 lr_eval_string("{arrive}"));
		
			web_reg_find("Fail=NotFound",
				"Text={web_string}",
				LAST);
			
			web_submit_data("reservations.pl_3",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t6.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=firstName", "Value={fname}", ENDITEM,
				"Name=lastName", "Value={lname}", ENDITEM,
				"Name=address1", "Value={street}", ENDITEM,
				"Name=address2", "Value={city}", ENDITEM,
				"Name=pass1", "Value={fname} {lname}", ENDITEM,
				"Name=creditCard", "Value={card}", ENDITEM,
				"Name=expDate", "Value={exp_date}", ENDITEM,
				"Name=oldCCOption", "Value=", ENDITEM,
				"Name=numPassengers", "Value=1", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				"Name=outboundFlight", "Value={outboundFlight_id}", ENDITEM,
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=returnFlight", "Value=", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				"Name=buyFlights.x", "Value=47", ENDITEM,
				"Name=buyFlights.y", "Value=12", ENDITEM,
				"Name=.cgifields", "Value=saveCC", ENDITEM,
				LAST);

		lr_end_transaction("click_book",LR_AUTO);

		lr_start_transaction("click_itinerary");

			web_add_auto_header("Sec-Fetch-User", 
				"?1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(5);

			lr_param_sprintf("web_string_new", "%s\n :  %sm : Flight %s leaves %s  for %s",
			                 lr_eval_string("{departDate}"),
			                 lr_paramarr_idx("flight_hour", random_number),
			                 lr_paramarr_idx("flight_number", random_number),
							 lr_eval_string("{depart}"),
							 lr_eval_string("{arrive}"));				
			
			web_reg_find("Fail=NotFound",
				"Text={web_string_new}",
				LAST);
			
			web_reg_save_param("flight_id",
				"LB=name=\"flightID\" value=\"",
				"RB=\"",
				LAST);
			web_reg_save_param("flight_id_part",
				"LB=name=\"flightID\" value=\"",
				"RB=-",
				"Ord=ALL",
				LAST);	
			
			web_url("Itinerary Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t10.inf", 
				"Mode=HTML", 
				LAST);
			
			for(i = 1; i <= lr_paramarr_len("flight_id_part"); i++)
			{
				if( !strcmp(lr_paramarr_idx("flight_id_part", i), lr_paramarr_idx("flight_id_part", 1)) )
				{
					count++;
				}
			}
		
		lr_end_transaction("click_itinerary",LR_AUTO);

		lr_start_transaction("click_cancel_ckecked");

			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(5);
			
			if(lr_paramarr_len("flight_id_part") == 1){
				
				web_reg_find("Fail=NotFound",
				"Text=<H3>No flights have been reserved.</H3>",
				LAST);
				
			} else {
				
				web_reg_save_param("flight_id_response",
					"LB=name=\"flightID\" value=\"",
					"RB=\"",
					LAST);
				web_reg_save_param("flight_id_part_res",
					"LB=name=\"flightID\" value=\"",
					"RB=-",
					"Ord=ALL",
					LAST);
			}
			
			web_submit_form("itinerary.pl",
				ITEMDATA,
				"Name=1", "Value=on", ENDITEM,
				"Name=removeFlights.x", "Value=46", ENDITEM, 
				"Name=removeFlights.y", "Value=11", ENDITEM,
				LAST);
					
			if( (lr_paramarr_len("flight_id_part") > 1) &&
			  		!strcmp(lr_eval_string("{flight_id}"), lr_eval_string("{flight_id_response}")) )
			{
					for(i = 1; i <= lr_paramarr_len("flight_id_part_res"); i++)
					{
						if( !strcmp(lr_paramarr_idx("flight_id_part_res", i), lr_paramarr_idx("flight_id_part", 1)) )
						{
							count_response++;
						}
					}
										
					if(count <= count_response)
					{
						lr_error_message("Error: count is equal or less than count_response.");
					}
			}
		
		lr_end_transaction("click_cancel_ckecked",LR_AUTO);

		lr_start_transaction("click_sign_off");

			web_add_header("Sec-Fetch-User", 
				"?1");
		
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(5);
			
			web_reg_find("Fail=NotFound",
						"Text= A Session ID has been created and loaded into a cookie called MSO",
						LAST);
			
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("click_sign_off",LR_AUTO);

	lr_end_transaction("05_CancelFlight",LR_AUTO);

	return 0;
}