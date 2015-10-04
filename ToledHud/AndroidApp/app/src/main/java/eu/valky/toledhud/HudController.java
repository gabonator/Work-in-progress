package eu.valky.toledhud;

import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.content.Context;
import android.app.Activity;

public class HudController //extends Activity // TODO: len kvoli reg receiver
{
    private Bundle mData;
    private ToledData mToled;
    private Handler mHandler;
    private Context mContext;
    private SygicUpdatesReceiver mSygicReceiver;
    // Settings
    private CSygicFormatting mFormatter;

    HudController(Context context, Handler handler)
    {
        mHandler = handler;
        mContext = context;
        mSygicReceiver = new SygicUpdatesReceiver(mHandler);
        IntentFilter filter = new IntentFilter(SygicUpdatesReceiver.INTENT_ACTION_UPDATE);
        context.registerReceiver(mSygicReceiver, filter);
        mToled = new ToledData();
        mFormatter = new CSygicFormatting();
    }

    public void onDestroy()
    {
        mContext.unregisterReceiver(mSygicReceiver);
    }

    public void UpdateFromIntent(Bundle data)
    {
        mData = data;
        updateHud();
    }

    public void setBacklight(int nValue)
    {
        sendRaw(mToled.GetFullPacket(mToled.GetBacklightPacket(6)));
    }

    public void setUnits(CSygicFormatting.SygicUnits eUnits)
    {
        mFormatter.setUnits(eUnits);
        updateHud();
    }

    private void updateHud()
    {
        int nTotalLength = 0;
        int nPassedLength = 0;
        int nDistance = 0;
        int nSpeedLimit = 0;
        int nVehicleSpeed = 0;
        int nDirectionPrimary = -1;
        int nDirectionSecondary = -1;

        if ( mData.containsKey("LengthToInstruction") )
            nDistance = mData.getInt("LengthToInstruction");
        if ( mData.containsKey("LengthTotal") )
            nTotalLength = mData.getInt("LengthTotal");
        if ( mData.containsKey("LengthPassed") )
            nPassedLength = mData.getInt("LengthPassed");
        if ( mData.containsKey("VehicleSpeed") )
            nVehicleSpeed = mData.getInt("VehicleSpeed");
        if ( mData.containsKey("SpeedLimit") )
            nSpeedLimit = mData.getInt("SpeedLimit");
        if ( mData.containsKey("DirCommandPrimary") )
            nDirectionPrimary = mData.getInt("DirCommandPrimary");
        if ( mData.containsKey("DirCommandSecondary") )
            nDirectionSecondary = mData.getInt("DirCommandSecondary");

        mToled.ePrimaryDirection = mFormatter.FromSygicDirection(nDirectionPrimary);
        mToled.eSecondaryDirection = mFormatter.FromSygicDirection(nDirectionSecondary);
        mToled.bRouteAvailable = true;

        CSygicFormatting.CLocalizedDistance pDistance;
        pDistance = mFormatter.LocalizedDistance(nDistance, true); //new CLocalizedDistance(nDistance);
        mToled.nPrimaryDistance = pDistance.m_nDistance;
        mToled.ePrimary = pDistance.m_eUnits;

        mToled.nSecondaryDistance = nDirectionSecondary != -1 ? 0 : -1;
        mToled.eSecondary = pDistance.m_eUnits;

        pDistance = mFormatter.LocalizedDistance(nTotalLength - nPassedLength, false);
        mToled.nDistanceToDestination = pDistance.m_nDistance;
        mToled.eDestination = pDistance.m_eUnits;

        mToled.nSpeedCameraDistance = -1;

        CSygicFormatting.CLocalizedSpeed pSpeed;
        pSpeed = mFormatter.LocalizedSpeed(nVehicleSpeed, false);
        mToled.nCurrentSpeed = pSpeed.m_nSpeed;
        mToled.eSpeed = pSpeed.m_eUnits;

        pSpeed = mFormatter.LocalizedSpeed(nSpeedLimit, true);
        mToled.nSpeedCameraLimit = pSpeed.m_nSpeed;
        mToled.eSpeedCamera = pSpeed.m_eUnits;

        requestUpdate();
    }

    public void requestUpdate()
    {
        sendRaw(mToled.GetFullPacket(mToled.GetInstructionsPacket()));
    }

    public void onConnect()
    {
      //  mToled.setWaiting();
      //  sendRaw(mToled.GetFullPacket(mToled.GetInstructionsPacket()));
    }

    public void sendRaw(byte[] data)
    {
        Message msg = mHandler.obtainMessage(MainActivity.MESSAGE_MAIN_SEND_RAW_DATA, null);
        Bundle bundle = new Bundle();
        bundle.putByteArray("tx", data);
        msg.setData(bundle);
        mHandler.sendMessage(msg);
    }
}
