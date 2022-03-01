/*************************** Wg ***************************/
{
	curr_msgq_length = Wg[_time_step%2][dim_1][dim_2].count;
	
	if ((pos(1) == 61)) {
		Wgff[dim_1][dim_2]=1;
	} else {
		Wgff[dim_1][dim_2]=2;
	/*by end_if()*/}
	_Wg_v10 = 10.0;
	Wg[(_time_step+1)%2][dim_1][dim_2].v10 = (Wg[_time_step%2][dim_1][dim_2].v * _Wg_v10);
}
/*************************** Fz ***************************/
{
	curr_msgq_length = Fz[_time_step%2][dim_1][dim_2].count;
	
}
/*************************** FzB ***************************/
{
	curr_msgq_length = FzB[_time_step%2][dim_1][dim_2].count;
	
	FzB[(_time_step+1)%2][dim_1][dim_2].v10 = (FzB[_time_step%2][dim_1][dim_2].v * 10.0);
	if ((FzB[_time_step%2][dim_1][dim_2].v > 0.011)) {
		
		strcpy(Ntm[(_time_step+1)%2][dim_1][dim_2].msgq[Ntm[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		Ntm[(_time_step+1)%2][dim_1][dim_2].msgq[Ntm[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Ntm[(_time_step+1)%2][dim_1][dim_2].msgq[Ntm[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Ntm[(_time_step+1)%2][dim_1][dim_2].msgq[Ntm[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "FzB");
		Ntm[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Ntm[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Ntm. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if ((FzB[_time_step%2][dim_1][dim_2].v > 0.004)) {
		
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "FzB");
		Vg[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Vg[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Vg. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if ((FzB[_time_step%2][dim_1][dim_2].v > 0.004)) {
		
		strcpy(X[(_time_step+1)%2][dim_1][dim_2].msgq[X[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		X[(_time_step+1)%2][dim_1][dim_2].msgq[X[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		X[(_time_step+1)%2][dim_1][dim_2].msgq[X[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(X[(_time_step+1)%2][dim_1][dim_2].msgq[X[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "FzB");
		X[(_time_step+1)%2][dim_1][dim_2].count++;
		if (X[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in X. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	
	{
		int _msgvalue_1804289383 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < FzB[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Rep") == 0) && 
		(strcmp(FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Ntm") == 0) && 
		(FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1804289383 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1804289383) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < FzB[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "FzB" , tmp1, tmp2);
			set_screen(full_signal);
			
			FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			FzB[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		FzB[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Ntm ***************************/
{
	curr_msgq_length = Ntm[_time_step%2][dim_1][dim_2].count;
	
	if ((_t0 < 60)) {
		Ntmff[dim_1][dim_2]=1;
	} else {
		Ntmff[dim_1][dim_2]=2;
	/*by end_if()*/}
	if ((Ntm[_time_step%2][dim_1][dim_2].v > 0.1)) {
		
		strcpy(FzB[(_time_step+1)%2][dim_1][dim_2].msgq[FzB[(_time_step+1)%2][dim_1][dim_2].count].signal, "Rep");
		FzB[(_time_step+1)%2][dim_1][dim_2].msgq[FzB[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		FzB[(_time_step+1)%2][dim_1][dim_2].msgq[FzB[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(FzB[(_time_step+1)%2][dim_1][dim_2].msgq[FzB[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Ntm");
		FzB[(_time_step+1)%2][dim_1][dim_2].count++;
		if (FzB[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in FzB. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	
	{
		int _msgvalue_846930886 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Ntm[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "FzB") == 0) && 
		(Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_846930886 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_846930886) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Ntm[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Ntm" , tmp1, tmp2);
			set_screen(full_signal);
			
			Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Ntm[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Ntm[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** X ***************************/
{
	curr_msgq_length = X[_time_step%2][dim_1][dim_2].count;
	
	if ((_t0 < 60)) {
		Xff[dim_1][dim_2]=1;
	} else {
		Xff[dim_1][dim_2]=2;
	/*by end_if()*/}
	if ((X[_time_step%2][dim_1][dim_2].v > 0.05)) {
		
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].signal, "Rep");
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "X");
		Vg[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Vg[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Vg. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	
	{
		int _msgvalue_1681692777 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < X[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(X[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "FzB") == 0) && 
		(X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1681692777 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1681692777) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < X[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, X[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "X" , tmp1, tmp2);
			set_screen(full_signal);
			
			X[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			X[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			X[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		X[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Vg ***************************/
{
	curr_msgq_length = Vg[_time_step%2][dim_1][dim_2].count;
	
	
	{
		int _msgvalue_1714636915 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Vg[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Rep") == 0) && 
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "X") == 0) && 
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1714636915 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1714636915) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	
	{
		int _msgvalue_1957747793 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Vg[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "FzB") == 0) && 
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1957747793 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1957747793) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	
	{
		int _msgvalue_424238335 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Vg[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Vg") == 0) && 
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_424238335 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_424238335) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	
	{
		int _msgvalue_719885386 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Vg[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Yki") == 0) && 
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_719885386 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_719885386) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	if ((Vg[_time_step%2][dim_1][dim_2].v > 0.1)) {
		
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Vg");
		Vg[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Vg[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Vg. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if ((Vg[_time_step%2][dim_1][dim_2].v > 0.2)) {
		
		strcpy(Fj[(_time_step+1)%2][dim_1][dim_2].msgq[Fj[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		Fj[(_time_step+1)%2][dim_1][dim_2].msgq[Fj[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Fj[(_time_step+1)%2][dim_1][dim_2].msgq[Fj[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Fj[(_time_step+1)%2][dim_1][dim_2].msgq[Fj[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Vg");
		Fj[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Fj[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Fj. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if ((Vg[_time_step%2][dim_1][dim_2].v > 0.2)) {
		
		strcpy(Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].signal, "Rep");
		Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Vg");
		Ds_P[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Ds_P[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Ds_P. msgqsize is too small.");
		
		/*sendmsg*/
		
		strcpy(Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].signal, "Rep");
		Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Vg");
		Ds_D[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Ds_D[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Ds_D. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Vg[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Vg" , tmp1, tmp2);
			set_screen(full_signal);
			
			Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Vg[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Vg[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Fj ***************************/
{
	curr_msgq_length = Fj[_time_step%2][dim_1][dim_2].count;
	
	
	{
		int _msgvalue_1649760492 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Fj[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Vg") == 0) && 
		(Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1649760492 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1649760492) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Fj[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Fj" , tmp1, tmp2);
			set_screen(full_signal);
			
			Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Fj[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Fj[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Ds_P ***************************/
{
	curr_msgq_length = Ds_P[_time_step%2][dim_1][dim_2].count;
	
	if (((((pos(1) < 50) && (pos(1) > 35)) && (pos(2) < 50)) && (pos(2) > 35))) {
		Ds_Pff[dim_1][dim_2]=1;
	} else {
		Ds_Pff[dim_1][dim_2]=2;
	/*by end_if()*/}
	
	{
		int _msgvalue_596516649 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Ds_P[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Rep") == 0) && 
		(strcmp(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Vg") == 0) && 
		(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_596516649 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_596516649) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	
	{
		int _msgvalue_1189641421 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Ds_P[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Ubq") == 0) && 
		(strcmp(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "F7_P") == 0) && 
		(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1189641421 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1189641421) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Ds_P[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Ds_P" , tmp1, tmp2);
			set_screen(full_signal);
			
			Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Ds_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Ds_P[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Ds_D ***************************/
{
	curr_msgq_length = Ds_D[_time_step%2][dim_1][dim_2].count;
	
	if (((((pos(1) < 50) && (pos(1) > 35)) && (pos(2) < 50)) && (pos(2) > 35))) {
		Ds_Dff[dim_1][dim_2]=1;
	} else {
		Ds_Dff[dim_1][dim_2]=2;
	/*by end_if()*/}
	
	{
		int _msgvalue_1025202362 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Ds_D[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Rep") == 0) && 
		(strcmp(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Vg") == 0) && 
		(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1025202362 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1025202362) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	
	{
		int _msgvalue_1350490027 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Ds_D[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Ubq") == 0) && 
		(strcmp(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "F7_D") == 0) && 
		(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1350490027 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1350490027) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Ds_D[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Ds_D" , tmp1, tmp2);
			set_screen(full_signal);
			
			Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Ds_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Ds_D[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Ft_P ***************************/
{
	curr_msgq_length = Ft_P[_time_step%2][dim_1][dim_2].count;
	
}
/*************************** Ft_D ***************************/
{
	curr_msgq_length = Ft_D[_time_step%2][dim_1][dim_2].count;
	
}
/*************************** F7_P ***************************/
{
	curr_msgq_length = F7_P[_time_step%2][dim_1][dim_2].count;
	
	if (((FtF7_P[_time_step%2][dim_1][dim_2].v + F7_P[_time_step%2][dim_1][dim_2].v) > 0.7)) {
		
		strcpy(D_P[(_time_step+1)%2][dim_1][dim_2].msgq[D_P[(_time_step+1)%2][dim_1][dim_2].count].signal, "Ubq");
		D_P[(_time_step+1)%2][dim_1][dim_2].msgq[D_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		D_P[(_time_step+1)%2][dim_1][dim_2].msgq[D_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(D_P[(_time_step+1)%2][dim_1][dim_2].msgq[D_P[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "F7_P");
		D_P[(_time_step+1)%2][dim_1][dim_2].count++;
		if (D_P[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in D_P. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if (((FtF7_P[_time_step%2][dim_1][dim_2].v + F7_P[_time_step%2][dim_1][dim_2].v) > 0.7)) {
		
		strcpy(Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].signal, "Ubq");
		Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Ds_P[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_P[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "F7_P");
		Ds_P[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Ds_P[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Ds_P. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if (((FtF7_P[_time_step%2][dim_1][dim_2].v + F7_P[_time_step%2][dim_1][dim_2].v) > 0.7)) {
		
		strcpy(DDs_P[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_P[(_time_step+1)%2][dim_1][dim_2].count].signal, "Ubq");
		DDs_P[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		DDs_P[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_P[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(DDs_P[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_P[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "F7_P");
		DDs_P[(_time_step+1)%2][dim_1][dim_2].count++;
		if (DDs_P[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in DDs_P. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < F7_P[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "F7_P" , tmp1, tmp2);
			set_screen(full_signal);
			
			F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			F7_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		F7_P[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** F7_D ***************************/
{
	curr_msgq_length = F7_D[_time_step%2][dim_1][dim_2].count;
	
	if (((FtF7_D[_time_step%2][dim_1][dim_2].v + F7_D[_time_step%2][dim_1][dim_2].v) > 0.7)) {
		
		strcpy(D_D[(_time_step+1)%2][dim_1][dim_2].msgq[D_D[(_time_step+1)%2][dim_1][dim_2].count].signal, "Ubq");
		D_D[(_time_step+1)%2][dim_1][dim_2].msgq[D_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		D_D[(_time_step+1)%2][dim_1][dim_2].msgq[D_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(D_D[(_time_step+1)%2][dim_1][dim_2].msgq[D_D[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "F7_D");
		D_D[(_time_step+1)%2][dim_1][dim_2].count++;
		if (D_D[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in D_D. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if (((FtF7_D[_time_step%2][dim_1][dim_2].v + F7_D[_time_step%2][dim_1][dim_2].v) > 0.7)) {
		
		strcpy(Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].signal, "Ubq");
		Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Ds_D[(_time_step+1)%2][dim_1][dim_2].msgq[Ds_D[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "F7_D");
		Ds_D[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Ds_D[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Ds_D. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if (((FtF7_D[_time_step%2][dim_1][dim_2].v + F7_D[_time_step%2][dim_1][dim_2].v) > 0.7)) {
		
		strcpy(DDs_D[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_D[(_time_step+1)%2][dim_1][dim_2].count].signal, "Ubq");
		DDs_D[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		DDs_D[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_D[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(DDs_D[(_time_step+1)%2][dim_1][dim_2].msgq[DDs_D[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "F7_D");
		DDs_D[(_time_step+1)%2][dim_1][dim_2].count++;
		if (DDs_D[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in DDs_D. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < F7_D[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "F7_D" , tmp1, tmp2);
			set_screen(full_signal);
			
			F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			F7_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		F7_D[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** FtF7_P ***************************/
{
	curr_msgq_length = FtF7_P[_time_step%2][dim_1][dim_2].count;
	
}
/*************************** FtF7_D ***************************/
{
	curr_msgq_length = FtF7_D[_time_step%2][dim_1][dim_2].count;
	
}
/*************************** D_P ***************************/
{
	curr_msgq_length = D_P[_time_step%2][dim_1][dim_2].count;
	
	
	{
		int _msgvalue_783368690 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < D_P[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Ubq") == 0) && 
		(strcmp(D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "F7_P") == 0) && 
		(D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_783368690 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_783368690) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < D_P[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "D_P" , tmp1, tmp2);
			set_screen(full_signal);
			
			D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			D_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		D_P[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** D_D ***************************/
{
	curr_msgq_length = D_D[_time_step%2][dim_1][dim_2].count;
	
	if (((D_P[_time_step%2][dim_1][dim_2].v + D_D[_time_step%2][dim_1][dim_2].v) > 0.1)) {
		
		strcpy(Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].signal, "Rep");
		Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "D_D");
		Wts[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Wts[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Wts. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	
	{
		int _msgvalue_1102520059 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < D_D[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Ubq") == 0) && 
		(strcmp(D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "F7_D") == 0) && 
		(D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1102520059 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1102520059) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < D_D[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "D_D" , tmp1, tmp2);
			set_screen(full_signal);
			
			D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			D_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		D_D[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** DDs_P ***************************/
{
	curr_msgq_length = DDs_P[_time_step%2][dim_1][dim_2].count;
	
	
	{
		int _msgvalue_2044897763 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < DDs_P[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Ubq") == 0) && 
		(strcmp(DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "F7_P") == 0) && 
		(DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_2044897763 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_2044897763) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < DDs_P[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "DDs_P" , tmp1, tmp2);
			set_screen(full_signal);
			
			DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			DDs_P[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		DDs_P[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** DDs_D ***************************/
{
	curr_msgq_length = DDs_D[_time_step%2][dim_1][dim_2].count;
	
	
	{
		int _msgvalue_1967513926 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < DDs_D[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Ubq") == 0) && 
		(strcmp(DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "F7_D") == 0) && 
		(DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1967513926 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1967513926) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < DDs_D[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "DDs_D" , tmp1, tmp2);
			set_screen(full_signal);
			
			DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			DDs_D[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		DDs_D[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Wts ***************************/
{
	curr_msgq_length = Wts[_time_step%2][dim_1][dim_2].count;
	
	_Wts_alltension = 0.0;
	_Wts_tension = 0.0;
	{
		register int _i;
		for (_i = INDEX_1_LB; _i <= INDEX_1_UB; _i++) {
			/*begin_forall*/
			{
				register int _j;
				for (_j = INDEX_2_LB; _j <= INDEX_2_UB; _j++) {
					/*begin_forall*/
					
					{
						int _msgvalue_1365180540 = 0;
						msgcount = 0;
						for (msgcount = 0; msgcount < Wts[_time_step%2][dim_1][dim_2].count; msgcount++) 
						if (
						(strcmp(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Tsn") == 0) && 
						(strcmp(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "cell") == 0) && 
						(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+(_i)) &&
						(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+(_j)) &&
						1 ) {
							_msgvalue_1365180540 = 1;
							_Wts_tension = _Wts_tension + Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo;
						}
						/*check_message()*/
						if (_msgvalue_1365180540) {
							_Wts_alltension = (_Wts_alltension + _Wts_tension);
						/*by end_if()*/}
					/*by end_if() for checkmsg_num*/}
				}
			}
			/*end_forall*/
		}
	}
	/*end_forall*/
	Wts[(_time_step+1)%2][dim_1][dim_2].t = (Wts[_time_step%2][dim_1][dim_2].t + _Wts_alltension);
	if ((Wts[_time_step%2][dim_1][dim_2].v > 0.1)) {
		
		strcpy(Yki[(_time_step+1)%2][dim_1][dim_2].msgq[Yki[(_time_step+1)%2][dim_1][dim_2].count].signal, "Rep");
		Yki[(_time_step+1)%2][dim_1][dim_2].msgq[Yki[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Yki[(_time_step+1)%2][dim_1][dim_2].msgq[Yki[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Yki[(_time_step+1)%2][dim_1][dim_2].msgq[Yki[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Wts");
		Yki[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Yki[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Yki. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	
	{
		int _msgvalue_1540383426 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Wts[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Act") == 0) && 
		(strcmp(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Yki") == 0) && 
		(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1540383426 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1540383426) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	
	{
		int _msgvalue_304089172 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Wts[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Rep") == 0) && 
		(strcmp(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "D_P") == 0) && 
		(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_304089172 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_304089172) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Wts[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Wts" , tmp1, tmp2);
			set_screen(full_signal);
			
			Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Wts[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Wts[_time_step%2][dim_1][dim_2].count = 0;
	}
}
/*************************** Yki ***************************/
{
	curr_msgq_length = Yki[_time_step%2][dim_1][dim_2].count;
	
	_Yki_vv = 1.5;
	_Yki_yy = 0.0;
	_Yki_yy = (_Yki_yy * _Yki_vv);
	
	{
		int _msgvalue_1303455736 = 0;
		msgcount = 0;
		for (msgcount = 0; msgcount < Yki[_time_step%2][dim_1][dim_2].count; msgcount++) 
		if (
		(strcmp(Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].signal, "Rep") == 0) && 
		(strcmp(Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj, "Wts") == 0) && 
		(Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 == dim_1+0) &&
		(Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 == dim_2+0) &&
		1 ) {
			_msgvalue_1303455736 = 1;
			break;
		}
		/*check_message()*/
		if (_msgvalue_1303455736) {
		/*by end_if()*/}
	/*by end_if() for checkmsg_num*/}
	if ((Yki[_time_step%2][dim_1][dim_2].v > 0.3)) {
		
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Vg[(_time_step+1)%2][dim_1][dim_2].msgq[Vg[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Yki");
		Vg[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Vg[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Vg. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	if ((Yki[_time_step%2][dim_1][dim_2].v > 0.2)) {
		
		Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].taginfo = _Yki_vv;
		strcpy(Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].signal, "Act");
		Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_1 = dim_1;
		Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].sender_cell_2 = dim_2;
		strcpy(Wts[(_time_step+1)%2][dim_1][dim_2].msgq[Wts[(_time_step+1)%2][dim_1][dim_2].count].sender_obj, "Yki");
		Wts[(_time_step+1)%2][dim_1][dim_2].count++;
		if (Wts[(_time_step+1)%2][dim_1][dim_2].count > 20)
			printf("Message queue overflow in Wts. msgqsize is too small.");
		
		/*sendmsg*/
	/*by end_if()*/}
	{
		char signal[256], sender[256], full_signal[256], tmp1[256], tmp2[256];
		int rel_1, rel_2, rel_3;
		
		for (msgcount = 0; msgcount < Yki[_time_step%2][dim_1][dim_2].count; msgcount++) {
			
			rel_1 = Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 - dim_1;
			rel_2 = Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 - dim_2;
			strcpy(signal, Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].signal);
			strcpy(sender, Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj);
			sprintf(tmp1, ((rel_1 != 0) ? ((rel_1 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_1));
			sprintf(tmp2, ((rel_2 != 0) ? ((rel_2 > 0) ? "p%d" : "n%d") : "%d"), abs(rel_2));
			sprintf(full_signal, "%s_%s_%s_%s_%s", sender, signal, "Yki" , tmp1, tmp2);
			set_screen(full_signal);
			
			Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].taginfo = 0.0;
			Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].signal[10] = '\0';
			Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_obj[10] = '\0';
			Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_1 = 0;
			Yki[_time_step%2][dim_1][dim_2].msgq[msgcount].sender_cell_2 = 0;
		}
		Yki[_time_step%2][dim_1][dim_2].count = 0;
	}
}
