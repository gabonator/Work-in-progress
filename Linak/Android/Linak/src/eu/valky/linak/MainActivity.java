package eu.valky.linak;

import java.io.UnsupportedEncodingException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import eu.valky.linak.R;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.PowerManager;
import android.os.SystemClock;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
import android.view.View.OnLongClickListener;
//import android.view.View.OnTouchListener;

public class MainActivity extends Activity
{	
	// Message types sent from the BluetoothRfcommClient Handler
    public static final int MESSAGE_STATE_CHANGE = 1;
    public static final int MESSAGE_READ = 2;
    public static final int MESSAGE_WRITE = 3;
    public static final int MESSAGE_DEVICE_NAME = 4;
    public static final int MESSAGE_TOAST = 5;

    private static final int REQUEST_CONNECT_DEVICE = 1;
    private static final int REQUEST_ENABLE_BT = 2;
    
	// Key names received from the BluetoothRfcommClient Handler
    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
                
    public String rxBuffer = null;

    // Layout Views
    private TextView mBTStatus;
    private Button mConnectButton;
    
    // Name of the connected device
    private String mConnectedDeviceName = null;
    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothRfcommClient mRfcommClient = null;
    
    private String lastCommand = null;
    private long lastCommandTime = 0;

    // stay awake
    protected PowerManager.WakeLock mWakeLock;
    
    private Handler mTimerHandler = new Handler();
    
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        // Set up the window layout
        requestWindowFeature(Window.FEATURE_NO_TITLE);        
        setContentView(R.layout.main);

        // Get local Bluetooth adapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        
        // If the adapter is null, then Bluetooth is not supported
        if (mBluetoothAdapter == null) {
            Toast.makeText(this, "Bluetooth is not available", Toast.LENGTH_LONG).show();
         //   finish();
            return;
        }
        
        // Prevent phone from sleeping
        PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        this.mWakeLock = pm.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "My Tag"); 
        this.mWakeLock.acquire();
        
        mTimerHandler.postDelayed(mTimerTask, 500);
        
        rxBuffer = new String();
    }

    private Runnable mTimerTask = new Runnable() {
        public void run() {
        	myTimer();
        	mHandler.postDelayed(this, 100);
        }
    };
     
    @Override
    public void onStart(){
    	super.onStart();
    	
    	// If BT is not on, request that it be enabled.
    	if (!mBluetoothAdapter.isEnabled()){
    		Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
    		startActivityForResult(enableIntent, REQUEST_ENABLE_BT);
    	}
    	// Otherwise, setup the Oscillosope session
    	else{
    		if (mRfcommClient == null) setup();
    	}    	
    }
    
    @Override
    public synchronized void onResume(){
    	super.onResume();
    	// Performing this check in onResume() covers the case in which BT was
        // not enabled during onStart(), so we were paused to enable it...
        // onResume() will be called when ACTION_REQUEST_ENABLE activity returns.
        if (mRfcommClient != null) {
            // Only if the state is STATE_NONE, do we know that we haven't started already
            if (mRfcommClient.getState() == BluetoothRfcommClient.STATE_NONE) {
              // Start the Bluetooth  RFCOMM services
              mRfcommClient.start();
            }
        }
    }
    
    @Override
    public void onDestroy(){
    	super.onDestroy();
    	// Stop the Bluetooth RFCOMM services
        if (mRfcommClient != null) mRfcommClient.stop();
        // release screen being on
        if (mWakeLock.isHeld()) { 
            mWakeLock.release();
        }
    }
        
    /**
     * Sends a message.
     * @param message  A string of text to send.
     */
    private void sendMessage(String message){
   	
    	// Check that we're actually connected before trying anything
    	if (mRfcommClient.getState() != BluetoothRfcommClient.STATE_CONNECTED) {
    		Toast.makeText(this, R.string.not_connected, Toast.LENGTH_SHORT).show();
    		return;
    	}
    	// Check that there's actually something to send
    	if (message.length() > 0) {
    		lastCommand = message;
    		lastCommandTime = SystemClock.uptimeMillis();
    		
    		// Get the message bytes and tell the BluetoothRfcommClient to write
    		byte[] send = message.getBytes();
    		mRfcommClient.write(send);
    	}
    }
  
    private void memoRecall(View v)
    {
    	Button btn = (Button)v;
    	String label = btn.getText().toString();
    	String cmd = "go "+label.substring(0,label.length()-2)+"\n";
    	sendMessage(cmd);
    }
    
    private void memoSave(View v)
    {
    	TextView text = (TextView) findViewById(R.id.textView);
    	Button btn = (Button)v;
    	Pattern p = Pattern.compile("\\((\\d+)",Pattern.DOTALL);
    	Matcher m = p.matcher(text.getText().toString());
    	if (m.find()) { 
    		btn.setText(m.group(1)+"cm");
    	}
    }
    
    private void myTimer()
    {
    	long lCurTime = SystemClock.uptimeMillis();
    	
    	if ( lastCommandTime != 0 && lCurTime - lastCommandTime > 200 )
    	{
    		// retry!
    		sendMessage( lastCommand );
    	}    	
    }
    
    private void setup()
    {
    	mBTStatus = (TextView) findViewById(R.id.txt_btstatus);
    	
    	mConnectButton = (Button) findViewById(R.id.button_connect);
    	mConnectButton.setOnClickListener(new OnClickListener(){
			public void onClick(View arg0) {
				BTConnect();
			}    		
    	});
 	
    	// Initialize the BluetoothRfcommClient to perform bluetooth connections
        mRfcommClient = new BluetoothRfcommClient(this, mHandler);
        
    	findViewById(R.id.button_up).setOnTouchListener(new View.OnTouchListener() {
    	    @Override
    	    public boolean onTouch(View v, MotionEvent event) {
    	        if(event.getAction() == MotionEvent.ACTION_DOWN) {    	        
    	            sendMessage("up\n");
    	        } else if (event.getAction() == MotionEvent.ACTION_UP) {
    	            sendMessage("stop\n");
    	        }
    	        return false;
    	    }
    	});

    	findViewById(R.id.button_down).setOnTouchListener(new View.OnTouchListener() {
    	    @Override
    	    public boolean onTouch(View v, MotionEvent event) {
    	        if(event.getAction() == MotionEvent.ACTION_DOWN) {
    	            sendMessage("down\n");
    	        } else if (event.getAction() == MotionEvent.ACTION_UP) {
    	            sendMessage("stop\n");
    	        }
    	        return false;
    	    }
    	}); 
    	
    	int arrButtons[] = {R.id.button_mem1, R.id.button_mem2, R.id.button_mem3, R.id.button_mem4};
    	for (int v : arrButtons)
    	{
    		Button btn = (Button)findViewById(v);

    		btn.setOnClickListener( new OnClickListener() {
    			@Override
        		public void onClick(View v) {
        			memoRecall(v);
        		}
        	});

    		btn.setOnLongClickListener(new OnLongClickListener() { 
                @Override
                public boolean onLongClick(View v) {
                	memoSave(v);
                    return true;
                }
            });    	
      	}    	
    }
    
    private void onReceive(String data) {
    	//EditText edit = (EditText) findViewById(R.id.info);
    	//edit.setText(data);
    	//Log.v("rx", data);
    	TextView text = (TextView) findViewById(R.id.textView);
    	text.setText(data);

    	// position
    	Pattern p = Pattern.compile("\\((.*?)\\)",Pattern.DOTALL);
    	Matcher m = p.matcher(data);
    	if (m.find()) { 
        	TextView position = (TextView) findViewById(R.id.position);
    		position.setText(m.group(1));
    	}

    	p = Pattern.compile("\\'(.*?)\\'",Pattern.DOTALL);
    	m = p.matcher(text.getText().toString());
    	if (m.find()) { 
    		String readCommand = m.group(1) + "\n";
    		if (lastCommand.equals(readCommand) )
    			lastCommandTime = 0;
    	}
    	
    }

    private void BTConnect(){
    	Intent serverIntent = new Intent(this, DeviceListActivity.class);
    	startActivityForResult(serverIntent, REQUEST_CONNECT_DEVICE);
    }
    
    // The Handler that gets information back from the BluetoothRfcommClient
    private final Handler mHandler = new Handler(){
    	@Override
        public void handleMessage(Message msg){
    		switch (msg.what){
    		case MESSAGE_STATE_CHANGE:
    			switch (msg.arg1){
    			case BluetoothRfcommClient.STATE_CONNECTED:
    				mBTStatus.setText(R.string.title_connected_to);
                    mBTStatus.append("\n" + mConnectedDeviceName);
    				break;
    			case BluetoothRfcommClient.STATE_CONNECTING:
    				mBTStatus.setText(R.string.title_connecting);
    				break;
    			case BluetoothRfcommClient.STATE_NONE:
    				mBTStatus.setText(R.string.title_not_connected);
    				break;
    			}
    			break;
    			
    		case MESSAGE_READ: // todo: implement receive data buffering
    			byte[] readBuf = (byte[]) msg.obj;
    			int len = msg.arg1;
    			String str = null;
				try {
					str = new String(readBuf, 0, len, "ASCII");
				} catch (UnsupportedEncodingException e) {
					e.printStackTrace();
				}
				
    			rxBuffer += str;//concat(str);
    			int nPos = -1;
    			String strLastCmd = null;
    			while ( (nPos = rxBuffer.indexOf("\n")) != -1 )
    			{
    				strLastCmd = rxBuffer.substring(0, nPos);
    				rxBuffer = rxBuffer.substring(nPos+1, rxBuffer.length());
    			}
    			if ( strLastCmd != null )
    				onReceive(strLastCmd);
    			// READ--------------
    			break;
    			
    		case MESSAGE_DEVICE_NAME:
    			// save the connected device's name
                mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);
                Toast.makeText(getApplicationContext(), "Connected to "
                        + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
    			break;
    			
    		case MESSAGE_TOAST:
    			Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                        Toast.LENGTH_SHORT).show();
    			break;
    		}
    	}
    };
    
    public void onActivityResult(int requestCode, int resultCode, Intent data){
    	switch (requestCode) {
    	case REQUEST_CONNECT_DEVICE:
    		// When DeviceListActivity returns with a device to connect
    		if (resultCode == Activity.RESULT_OK){
    			// Get the device MAC address
    			String address = data.getExtras().getString(DeviceListActivity.EXTRA_DEVICE_ADDRESS);
    			// Get the BLuetoothDevice object
                BluetoothDevice device = mBluetoothAdapter.getRemoteDevice(address);
                // Attempt to connect to the device
                mRfcommClient.connect(device);
    		}
    		break;
    	case REQUEST_ENABLE_BT:
    		// When the request to enable Bluetooth returns
            if (resultCode == Activity.RESULT_OK){
            	// Bluetooth is now enabled, so set up the oscilloscope
            	setup();
            }else{
            	// User did not enable Bluetooth or an error occured
                Toast.makeText(this, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
                finish();
            }
    		break;
    	}
    }
}
