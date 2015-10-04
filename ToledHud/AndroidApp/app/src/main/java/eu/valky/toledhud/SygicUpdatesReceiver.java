package eu.valky.toledhud;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class SygicUpdatesReceiver extends BroadcastReceiver {

	public static final String INTENT_ACTION_UPDATE = "com.sygic.intent.ACTION_HUD_UPDATE";
	
	private Handler mHandler;
	
	public SygicUpdatesReceiver(Handler handler) {
		mHandler = handler;
	}
	
	@Override
	public void onReceive(Context context, Intent intent) {
		if ( mHandler != null ) {
			Message msg = mHandler.obtainMessage(MainActivity.MESSAGE_MAIN_UPDATE_VALUES, null);
			Bundle data = intent.getExtras();
			msg.setData(data);
			mHandler.sendMessage(msg);
		}
	}
	
}
