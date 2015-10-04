package eu.valky.toledhud;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.PowerManager;
import android.widget.Toast;

public class BluetoothController
{
    // Messages
    public static final int MESSAGE_BT_STATE_CHANGE = 1;
    public static final int MESSAGE_BT_READ = 2;
    public static final int MESSAGE_BT_WRITE = 3;
    public static final int MESSAGE_BT_DEVICE_NAME = 4;

    public static final int REQUEST_BT_CONNECT_DEVICE = 1;
    public static final int REQUEST_BT_ENABLE_BT = 2;

    // Members
    private BluetoothAdapter mBluetoothAdapter = null;
    private BluetoothRfcommClient mRfcommClient = null;
    protected PowerManager.WakeLock mWakeLock;

    private Activity mContext;
    private Handler mHandler;

    // Implementation
    BluetoothController(Activity context, Handler handler) {
        mContext = context;
        mHandler = handler;

        // Get local Bluetooth adapter
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        // If the adapter is null, then Bluetooth is not supported
        if (mBluetoothAdapter == null) {
            Toast.makeText(mContext, "Bluetooth is not available", Toast.LENGTH_LONG).show();
            //   finish();
            return;
        }

        // Prevent phone from sleeping
        PowerManager pm = (PowerManager) mContext.getSystemService(Context.POWER_SERVICE);
        this.mWakeLock = pm.newWakeLock(PowerManager.SCREEN_BRIGHT_WAKE_LOCK, "My Tag");
        this.mWakeLock.acquire();
    }

    void onStart()
    {
        // If BT is not on, request that it be enabled.
        if (!mBluetoothAdapter.isEnabled()){
            Intent enableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            mContext.startActivityForResult(enableIntent, BluetoothController.REQUEST_BT_ENABLE_BT);
        }
        else {
            if (mRfcommClient == null) {
                Setup();
            }
        }
    }

    void onResume()
    {
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

    void onDestroy()
    {
        // Stop the Bluetooth RFCOMM services
        if (mRfcommClient != null) mRfcommClient.stop();
        // release screen being on
        if (mWakeLock.isHeld()) {
            mWakeLock.release();
        }
    }

    void Setup()
    {
        // Initialize the BluetoothRfcommClient to perform bluetooth connections
        mRfcommClient = new BluetoothRfcommClient(mContext, mHandler);
    }

    void Send(byte[] data)
    {
        // Check that we're actually connected before trying anything
        if (mRfcommClient.getState() != BluetoothRfcommClient.STATE_CONNECTED)
            return;

        mRfcommClient.write(data);
    }

    void Connect()
    {
        Intent serverIntent = new Intent(mContext, DeviceListActivity.class);
        mContext.startActivityForResult(serverIntent, BluetoothController.REQUEST_BT_CONNECT_DEVICE);
    }

    public void onActivityResult(int requestCode, int resultCode, Intent data){
        switch (requestCode) {
            case BluetoothController.REQUEST_BT_CONNECT_DEVICE:
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
            case BluetoothController.REQUEST_BT_ENABLE_BT:
                // When the request to enable Bluetooth returns
                if (resultCode == Activity.RESULT_OK){
                    // Bluetooth is now enabled, so set up the oscilloscope
                    Setup();
                }else{
                    // User did not enable Bluetooth or an error occured
                    Toast.makeText(mContext, R.string.bt_not_enabled_leaving, Toast.LENGTH_SHORT).show();
                    ///finish();
                }
                break;
        }
    }

    public boolean isConnected()
    {
        return mRfcommClient.getState() == BluetoothRfcommClient.STATE_CONNECTED;
    }
}
