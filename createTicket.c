createTicket()
{	
	int i, k, count, price, randomNumber;
	char paramName[100];//, s[100];
    char separators[] = ";";
    char *token;

	tName = "8.2.01.Choice_City";
	lr_start_transaction(tName);
	
    randomNumber = rand()%2;

	status = web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	end_transaction(tName, status);
	lr_think_time(4);

	lr_save_string(lr_eval_string("{seatPref}"),"sPref");
//	lr_output_message(lr_eval_string("{sPref}"));
	lr_save_string(lr_eval_string("{seatType}"),"sType");
//	lr_output_message(lr_eval_string("{sType}"));
	
	if (randomNumber == 0) {
		tName = "8.1.02.Choice_Flight";
		lr_start_transaction(tName);

		web_reg_save_param_ex(
		    "ParamName=outFlight", 
		    "LB/IC=name=\"outboundFlight\" value=\"",
		    "RB/IC=\"",
		    "Ordinal=all");
	
		status = web_submit_data("reservations.pl", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=depart", "Value={city}", ENDITEM, 
			"Name=departDate", "Value={date1}", ENDITEM, 
			"Name=arrive", "Value={city}", ENDITEM, 
			"Name=returnDate", "Value={date2}", ENDITEM, 
			"Name=numPassengers", "Value=1", ENDITEM, 
			"Name=roundtrip", "Value=<OFF>", ENDITEM, 
			"Name=seatPref", "Value={sPref}", ENDITEM, 
			"Name=seatType", "Value={sType}", ENDITEM, 
			"Name=findFlights.x", "Value=64", ENDITEM, 
			"Name=findFlights.y", "Value=11", ENDITEM, 
			LAST);
			
		end_transaction(tName, status);
		lr_think_time(4);

		tName = "8.2.03.Choice_Flight";
		lr_start_transaction(tName);

		count = atoi(lr_eval_string("{outFlight_count}"));
		
		k = 0;
		for (i = 1; i <= count; i++) {
			sprintf(paramName, "{outFlight_%d}", i);
			
		    token = (char *)strtok(lr_eval_string(paramName), separators);
			token[strlen(token) - 1] = 0;
			token = (char *)strtok(NULL, separators);
			price = atoi(token);
	
//			lr_output_message("Цена рейса %s равна: %d", lr_eval_string(paramName), price);
	
	   		if (price % 2 == 0) {
				k = 1;
				break;
	   		}
		}
		
		if (k == 0) {
			lr_output_message("Нет рейсов с четной ценой. Билет не создан.");
			return 0;
		}
		else {
			sprintf(paramName, "{outFlight_%d}", i);
			lr_param_sprintf("outF", lr_eval_string(paramName));
//			lr_output_message("Выбран рейс %s", lr_eval_string("{outF}"));
		}
		
		status = web_submit_data("reservations.pl_2", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
			"Snapshot=t5.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=outboundFlight", "Value={outF}", ENDITEM, 
			"Name=reserveFlights.x", "Value=3", ENDITEM, 
			"Name=reserveFlights.y", "Value=10", ENDITEM, 
			LAST);
	
		end_transaction(tName, status);
		lr_think_time(4);

		tName = "8.2.04.End_Booking";
		lr_start_transaction(tName);

		lr_save_string(lr_eval_string("{fName}"),"firstName");
//		lr_output_message(lr_eval_string("{firstName}"));
		lr_save_string(lr_eval_string("{sName}"),"secondName");
//		lr_output_message(lr_eval_string("{secondName}"));
		lr_save_string(lr_eval_string("{adress}"),"adr");
		lr_save_string(lr_eval_string("{home}"),"hom");
//		lr_output_message("Adress %s, %s", lr_eval_string("{adr}"),lr_eval_string("{hom}"));
		lr_save_string(lr_eval_string("{cCard}"),"creditCard");
		lr_save_string(lr_eval_string("{cDate}"),"creditDate");
//		lr_output_message("Credit card %s, %s", lr_eval_string("{creditCard}"),lr_eval_string("{creditDate}"));
	
		status = web_submit_data("reservations.pl_3", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
			"Snapshot=t6.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=firstName", "Value={firstName}", ENDITEM, 
			"Name=lastName", "Value={secondName}", ENDITEM, 
			"Name=address1", "Value={adr}", ENDITEM, 
			"Name=address2", "Value={hom}", ENDITEM, 
			"Name=pass1", "Value={firstName} {secondName}", ENDITEM, 
			"Name=creditCard", "Value={creditCard}", ENDITEM, 
			"Name=expDate", "Value={creditDate}", ENDITEM, 
			"Name=saveCC", "Value={randBoolean}", ENDITEM, 
			"Name=buyFlights.x", "Value=49", ENDITEM, 
			"Name=buyFlights.y", "Value=14", ENDITEM, 
			LAST);
		
		end_transaction(tName, status);
		lr_think_time(4);

	}
	else {
		tName = "8.1.02.Choice_Flight";
		lr_start_transaction(tName);

		web_reg_save_param_ex(
		    "ParamName=outFlight", 
		    "LB/IC=name=\"outboundFlight\" value=\"",
		    "RB/IC=\"",
		    "Ordinal=all");
		
		web_reg_save_param_ex(
		    "ParamName=returnFlight", 
		    "LB/IC=name=\"returnFlight\" value=\"",
		    "RB/IC=\"",
		    "Ordinal=all");
		
		status = web_submit_data("reservations.pl", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
			"Snapshot=t4.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=depart", "Value={city}", ENDITEM, 
			"Name=departDate", "Value={date1}", ENDITEM, 
			"Name=arrive", "Value={city}", ENDITEM, 
			"Name=returnDate", "Value={date2}", ENDITEM, 
			"Name=numPassengers", "Value=1", ENDITEM, 
			"Name=roundtrip", "Value=on", ENDITEM, 
			"Name=seatPref", "Value={sPref}", ENDITEM, 
			"Name=seatType", "Value={sType}", ENDITEM, 
			"Name=findFlights.x", "Value=64", ENDITEM, 
			"Name=findFlights.y", "Value=11", ENDITEM, 
			LAST);
		
		end_transaction(tName, status);
		lr_think_time(4);

		tName = "8.2.03.Choice_Flight";
		lr_start_transaction(tName);

		count = atoi(lr_eval_string("{outFlight_count}"));
		
		k = 0;
		for (i = 1; i <= count; i++) {
			sprintf(paramName, "{outFlight_%d}", i);
			
		    token = (char *)strtok(lr_eval_string(paramName), separators);
			token[strlen(token) - 1] = 0;
			token = (char *)strtok(NULL, separators);
			price = atoi(token);
	
	//		lr_output_message("Цена рейса %s равна: %d", lr_eval_string(paramName), price);
	
	   		if (price % 2 == 0) {
				k = 1;
				break;
	   		}
		}
		
		if (k == 0) {
			lr_output_message("Нет рейсов с четной ценой. Билет не создан.");
			return 0;
		}
		else {
			sprintf(paramName, "{outFlight_%d}", i);
			lr_param_sprintf("outF", lr_eval_string(paramName));
	//		lr_output_message("Выбран рейс %s", lr_eval_string("{outF}"));
		}
		lr_save_string(lr_eval_string(lr_paramarr_random("returnFlight")),"randomTicket2");
//		lr_output_message(lr_eval_string("{randomTicket2}"));
	
		status = web_submit_data("reservations.pl_2", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
			"Snapshot=t5.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=outboundFlight", "Value={outF}", ENDITEM, 
			"Name=returnFlight", "Value={randomTicket2}", ENDITEM, 
			"Name=reserveFlights.x", "Value=3", ENDITEM, 
			"Name=reserveFlights.y", "Value=10", ENDITEM, 
			LAST);
	
		end_transaction(tName, status);
		lr_think_time(4);

		tName = "8.2.04.End_Booking";
		lr_start_transaction(tName);

		lr_save_string(lr_eval_string("{fName}"),"firstName");
//		lr_output_message(lr_eval_string("{firstName}"));
		lr_save_string(lr_eval_string("{sName}"),"secondName");
//		lr_output_message(lr_eval_string("{secondName}"));
		lr_save_string(lr_eval_string("{adress}"),"adr");
		lr_save_string(lr_eval_string("{home}"),"hom");
//		lr_output_message("Adress %s, %s", lr_eval_string("{adr}"),lr_eval_string("{hom}"));
		lr_save_string(lr_eval_string("{cCard}"),"creditCard");
		lr_save_string(lr_eval_string("{cDate}"),"creditDate");
//		lr_output_message("Credit card %s, %s", lr_eval_string("{creditCard}"),lr_eval_string("{creditDate}"));
	
		status = web_submit_data("reservations.pl_3", 
			"Action=http://localhost:1080/cgi-bin/reservations.pl", 
			"Method=POST", 
			"TargetFrame=", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
			"Snapshot=t6.inf", 
			"Mode=HTML", 
			ITEMDATA, 
			"Name=firstName", "Value={firstName}", ENDITEM, 
			"Name=lastName", "Value={secondName}", ENDITEM, 
			"Name=address1", "Value={adr}", ENDITEM, 
			"Name=address2", "Value={hom}", ENDITEM, 
			"Name=pass1", "Value={firstName} {secondName}", ENDITEM, 
			"Name=creditCard", "Value={creditCard}", ENDITEM, 
			"Name=expDate", "Value={creditDate}", ENDITEM, 
			"Name=saveCC", "Value={randBoolean}", ENDITEM, 
			"Name=buyFlights.x", "Value=49", ENDITEM, 
			"Name=buyFlights.y", "Value=14", ENDITEM, 
			LAST);
		
		end_transaction(tName, status);
		lr_think_time(4);

	}
	
	return 0;
}
