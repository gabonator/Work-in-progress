package com.sygic.demomfdreceiver;

import android.app.Activity;
import android.content.IntentFilter;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class MainActivity extends Activity {

	public static final int MSG_UPDATE_VALUES = 1;
	private final String TAG = "DemoMFD";

	private SygicUpdatesReceiver mSygicReceiver;
	private Bundle mData;
	private TableLayout mTable;
	
	private boolean mIsInBackground = true;
	
	Handler mHandler = new Handler(new Handler.Callback() {
		
		@Override
		public boolean handleMessage(Message msg) {
			if(msg.what == MSG_UPDATE_VALUES) {
				mData = msg.getData();
				showValues();
				return true;
			}
			return false;
		}
	});
	
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mTable = (TableLayout)findViewById(R.id.layoutTable);
        
        mSygicReceiver = new SygicUpdatesReceiver(mHandler); 
		IntentFilter filter = new IntentFilter(SygicUpdatesReceiver.INTENT_ACTION_UPDATE);
		registerReceiver(mSygicReceiver, filter);
    }

	@Override
	protected void onResume() {
		mIsInBackground = false;
		super.onResume();
	}
        
	@Override
	protected void onPause() {
		mIsInBackground = true;
		super.onPause();
	}
	
	
	
	@Override
	protected void onDestroy() {
		unregisterReceiver(mSygicReceiver);
		super.onDestroy();
	}
	
	private void showValues() {
		
		if(!mIsInBackground) {
			mTable.removeAllViews();
		} 
		else {
			Log.d(TAG, "__________________");
		}

		showValueString("City");
		showValueString("Street");
		showValueInt("LengthToInstruction");
		showValueInt("LengthTotal");
		showValueInt("LengthPassed");
		showValueInt("SpeedLimit");
		showValueInt("TimeRemaining");
		showValueIntArray("PrimaryChars");
	}

	private void showValueInt(String key) {
		if(mData.containsKey(key)) {
			int nVal = mData.getInt(key);
			String sVal = nVal < 0 ? " - " : String.valueOf(nVal);
			showValue(key, sVal);
		}
	}

	private void showValueIntArray(String key) {
		if(mData.containsKey(key)) {
			int[] values = mData.getIntArray(key);
			StringBuilder sb = new StringBuilder();
			for(int i = 0; i < values.length; i++) {
				sb.append(values[i]).append(" ");
			}
			showValue(key, sb.toString());
		}
	}
	
	private void showValueString(String key) {
		if(mData.containsKey(key)) {
			showValue(key, mData.getString(key));
		}
	}
	
	private void showValue(String key, String value) {
		if(mIsInBackground) {
			Log.d(TAG, key + ": " + value);
		}
		else {
			addRow(key, value);
		}
	}
	
	
	private void addRow(String key, String value) {
		TextView tvKey = new TextView(this);
		tvKey.setText(key);
		tvKey.setPadding(0, 0, 10, 0);
		tvKey.setTypeface(null, Typeface.BOLD);
		
		TextView tvValue = new TextView(this);
		tvValue.setText(value);
		
		TableRow row = new TableRow(this);
		row.addView(tvKey);
		row.addView(tvValue);
		
		mTable.addView(row);
	}

}
