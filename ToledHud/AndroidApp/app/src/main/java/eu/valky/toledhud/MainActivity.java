package eu.valky.toledhud;

import eu.valky.toledhud.R;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.PowerManager;
import android.provider.MediaStore;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;
import android.widget.RadioGroup.OnCheckedChangeListener;

public class MainActivity extends Activity
{
    public static final int MESSAGE_MAIN_TOAST = 5;
	public static final int MESSAGE_MAIN_UPDATE_VALUES = 9121;
	public static final int MESSAGE_MAIN_SEND_RAW_DATA = 9213;

	public HudController mHudController;
    private BluetoothController mBtController;
    private String mConnectedDeviceName = null;

    public static final String DEVICE_NAME = "device_name";
    public static final String TOAST = "toast";
                
    public String rxBuffer = null;

    // Layout Views
    private TextView mBTStatus;
    private Button mConnectButton;
    private SeekBar mSliderBacklight;
    private RadioGroup mRadioUnits;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
		// Set up the window layout
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.main);

        mHudController = new HudController(this,mHandler);
        mBtController = new BluetoothController(this, mHandler);

        mBTStatus = (TextView) findViewById(R.id.textStatus);

        mConnectButton = (Button) findViewById(R.id.btnConnect);
        mConnectButton.setOnClickListener(new OnClickListener() {
            public void onClick(View arg0) {
                mBtController.Connect();
            }
        });

        mSliderBacklight = (SeekBar) findViewById(R.id.sliderLight);
        mSliderBacklight.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {
            int progressChanged = 0;

            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                mHudController.setBacklight(progress == 0 ? -1 : progress);
            }
            public void onStartTrackingTouch(SeekBar seekBar) {}
            public void onStopTrackingTouch(SeekBar seekBar) {}
        });

        mRadioUnits = (RadioGroup) findViewById(R.id.rbGroupUnits);
        mRadioUnits.setOnCheckedChangeListener(new OnCheckedChangeListener() {
               @Override
               public void onCheckedChanged(RadioGroup group, int checkedId) {

                   if (checkedId == R.id.rbUnitsKilometers) {
                       mHudController.setUnits(CSygicFormatting.SygicUnits.Kilometers);
                   } else if (checkedId == R.id.rbUnitsMiles) {
                       mHudController.setUnits(CSygicFormatting.SygicUnits.Miles);
                   }
               }
           });
    }

    @Override
    public void onStart(){
    	super.onStart();
        mBtController.onStart();
    }
    
    @Override
    public synchronized void onResume(){
    	super.onResume();
        mBtController.onResume();
    }
    
    @Override
    public void onDestroy(){
    	super.onDestroy();
        mBtController.onDestroy();
        mHudController.onDestroy();
    }

    void mainHandleMessage(Message msg)
    {
        switch (msg.what){
            case BluetoothController.MESSAGE_BT_STATE_CHANGE:
                switch (msg.arg1){
                    case BluetoothRfcommClient.STATE_CONNECTED:
                        mBTStatus.setText(R.string.title_connected_to);
                        mBTStatus.append("\n" + mConnectedDeviceName);
                        mHudController.onConnect();
                        break;
                    case BluetoothRfcommClient.STATE_CONNECTING:
                        mBTStatus.setText(R.string.title_connecting);
                        break;
                    case BluetoothRfcommClient.STATE_NONE:
                        mBTStatus.setText(R.string.title_not_connected);
                        break;
                }
                break;

            case BluetoothController.MESSAGE_BT_READ:
                break;

            case BluetoothController.MESSAGE_BT_DEVICE_NAME:
                // save the connected device's name
                mConnectedDeviceName = msg.getData().getString(DEVICE_NAME);
                Toast.makeText(getApplicationContext(), "Connected to "
                        + mConnectedDeviceName, Toast.LENGTH_SHORT).show();
                break;

            case MESSAGE_MAIN_TOAST:
                Toast.makeText(getApplicationContext(), msg.getData().getString(TOAST),
                        Toast.LENGTH_SHORT).show();
                break;

            case MESSAGE_MAIN_UPDATE_VALUES:
                if (mBtController.isConnected()) {
                    mHudController.UpdateFromIntent(msg.getData());
                }
                break;

            case MESSAGE_MAIN_SEND_RAW_DATA:
                Bundle bundle = msg.getData();
                byte[] send = bundle.getByteArray("tx");

                if (mBtController.isConnected())
                    mBtController.Send(send);
                else
                    Toast.makeText(this, R.string.not_connected, Toast.LENGTH_SHORT).show();
                break;
        }
    }

    private final Handler mHandler = new Handler(){
    	@Override
        public void handleMessage(Message msg){
            mainHandleMessage(msg);
    	}
    };
    
    public void onActivityResult(int requestCode, int resultCode, Intent data){
        mBtController.onActivityResult(requestCode, resultCode, data);
    }
}
