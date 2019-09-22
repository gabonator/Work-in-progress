package com.huoyuedianzi.hystagelight.ProtocolLevel;

import android.widget.ProgressBar;
import com.huoyuedianzi.hystagelight.BusinessLogicLevel.FilesManager.BaseFilesManager;
import com.huoyuedianzi.hystagelight.BusinessLogicLevel.FilesManager.TF_FilesManager;
import com.huoyuedianzi.hystagelight.BusinessLogicLevel.PatternDatasChangeManager;
import com.huoyuedianzi.hystagelight.GlobalConfig;
import com.huoyuedianzi.hystagelight.ModelLevel.CanvasScreen;
import com.huoyuedianzi.hystagelight.ModelLevel.Graphical;
import com.huoyuedianzi.hystagelight.ModelLevel.Scene;
import com.huoyuedianzi.hystagelight.ModelLevel.SceneItem;
import com.huoyuedianzi.hystagelight.ModelLevel.SceneSequence;
import com.huoyuedianzi.hystagelight.SystemDefinedLevel.Utils.System_DataType_Util;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import org.json.JSONArray;

public class LaserLightProtocol {
    private static LaserLightProtocol laserLightProtocol;
    public final byte DELETE_TFFILE = 19;
    public final byte GETDEVICE_PATAMETER = 7;
    public final byte SEARCH_DEVICE_FILES = 16;
    public final byte SETDEVICE_PATAMETER = 8;
    public final byte answerHeader = 90;
    public final byte answerTail = -86;
    public final byte askHeader = -86;
    public final byte askTail = 90;
    public final byte closeLightCode = 2;
    public final byte controlCode = 3;
    public final byte deviceSoftVersionCode = 1;
    private CanvasScreen mCanvasScreen;
    private PatternDatasChangeManager patternDatasChangeManager;
    public final byte readyFileCode = 17;
    public final byte readyPicDataCode = 5;
    public final byte sendDMXDataCode = 4;
    public final byte sendFileCode = 18;
    public final byte sendPicDataCode = 6;

    public LaserLightProtocol(CanvasScreen canvasScreen) {
        this.mCanvasScreen = canvasScreen;
        this.patternDatasChangeManager = new PatternDatasChangeManager(canvasScreen.width);
    }

    public static LaserLightProtocol getInstance(CanvasScreen canvasScreen) {
        if (laserLightProtocol == null) {
            synchronized (LaserLightProtocol.class) {
                if (laserLightProtocol == null) {
                    laserLightProtocol = new LaserLightProtocol(canvasScreen);
                }
            }
        }
        return laserLightProtocol;
    }

    private byte[] getOrderBytes(byte b, byte b2) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(b));
        arrayList.add(Byte.valueOf(b2));
        arrayList.add(Byte.valueOf(90));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getSoftVersionBytes() {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(1));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (arrayList.size() + 2)));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getCloseLightBytes() {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(2));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (arrayList.size() + 2)));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getControlCode(byte b) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(3));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (arrayList.size() + 3)));
        arrayList.add(Byte.valueOf(b));
        arrayList.add(Byte.valueOf(0));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getDMXDataBytes(List<Integer> list) {
        byte[] bArr = new byte[(list.size() + 6)];
        bArr[0] = -86;
        bArr[1] = 4;
        bArr[2] = 0;
        bArr[3] = 90;
        byte[] shortToByteArraySamllEndian = System_DataType_Util.shortToByteArraySamllEndian((short) bArr.length);
        bArr[4] = shortToByteArraySamllEndian[0];
        bArr[5] = shortToByteArraySamllEndian[1];
        for (int i = 0; i < list.size(); i++) {
            bArr[i + 6] = ((Integer) list.get(i)).byteValue();
        }
        return bArr;
    }

    public byte[] getDeviceFileBytes(byte[] bArr) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(16));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.add(Byte.valueOf(12));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        for (byte valueOf : bArr) {
            arrayList.add(Byte.valueOf(valueOf));
        }
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getReadyFileBytes(byte[] bArr, int i, byte b) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(17));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.add(Byte.valueOf(16));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        for (byte valueOf : bArr) {
            arrayList.add(Byte.valueOf(valueOf));
        }
        arrayList.add(Byte.valueOf(b));
        for (byte valueOf2 : System_DataType_Util.intToBytesSmallEndian(i)) {
            arrayList.add(Byte.valueOf(valueOf2));
        }
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getSendFileBytes(short s, String str, byte[] bArr) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(18));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) bArr.length));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(s));
        for (byte valueOf : str.getBytes()) {
            arrayList.add(Byte.valueOf(valueOf));
        }
        arrayList.add(Byte.valueOf(0));
        for (byte valueOf2 : bArr) {
            arrayList.add(Byte.valueOf(valueOf2));
        }
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getSendFileBytes(short s, byte[] bArr, byte[] bArr2) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(18));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (bArr2.length + 12)));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(s));
        for (byte valueOf : bArr) {
            arrayList.add(Byte.valueOf(valueOf));
        }
        for (byte valueOf2 : bArr2) {
            arrayList.add(Byte.valueOf(valueOf2));
        }
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] getTFFileData(SceneSequence sceneSequence, ProgressBar progressBar) {
        Iterator it;
        ProgressBar progressBar2 = progressBar;
        int i = 0;
        progressBar2.setProgress(0);
        LinkedList linkedList = new LinkedList();
        int patternsCount = sceneSequence.getPatternsCount();
        sceneSequence.updateRelationValue();
        for (int i2 = 0; i2 < 16; i2++) {
            linkedList.add(Byte.valueOf(0));
        }
        List sceneItemList = sceneSequence.getSceneItemList();
        linkedList.add(Byte.valueOf(48));
        linkedList.add(Byte.valueOf(0));
        linkedList.add(Byte.valueOf(0));
        linkedList.add(Byte.valueOf(0));
        int i3 = (4 * patternsCount) + 48 + 4;
        int size = ((short) ((SceneItem) sceneItemList.get(0)).getScene().getChannelByteList().size()) + 3;
        int size2 = (sceneItemList.size() * size) + i3;
        for (byte valueOf : System_DataType_Util.intToBytesSmallEndian(i3)) {
            linkedList.add(Byte.valueOf(valueOf));
        }
        int i4 = 1;
        linkedList.add(Byte.valueOf(1));
        linkedList.add(Byte.valueOf(0));
        for (byte valueOf2 : System_DataType_Util.shortToByteArraySamllEndian((short) size)) {
            linkedList.add(Byte.valueOf(valueOf2));
        }
        for (byte valueOf3 : System_DataType_Util.shortToByteArraySamllEndian((short) sceneItemList.size())) {
            linkedList.add(Byte.valueOf(valueOf3));
        }
        for (byte valueOf4 : System_DataType_Util.shortToByteArraySamllEndian((short) patternsCount)) {
            linkedList.add(Byte.valueOf(valueOf4));
        }
        for (byte valueOf5 : System_DataType_Util.shortToByteArraySamllEndian((short) 3)) {
            linkedList.add(Byte.valueOf(valueOf5));
        }
        for (int i5 = 0; i5 < 14; i5++) {
            linkedList.add(Byte.valueOf(0));
        }
        LinkedList linkedList2 = new LinkedList();
        LinkedList linkedList3 = new LinkedList();
        LinkedList linkedList4 = new LinkedList();
        progressBar2.setProgress(10);
        int size3 = 90 / sceneItemList.size();
        Iterator it2 = sceneItemList.iterator();
        int i6 = 0;
        int i7 = size2;
        int i8 = 0;
        while (it2.hasNext()) {
            SceneItem sceneItem = (SceneItem) it2.next();
            i8 += i4;
            for (byte valueOf6 : System_DataType_Util.shortToByteArraySamllEndian((short) (sceneItem.getPlayTime() / 10))) {
                linkedList3.add(Byte.valueOf(valueOf6));
            }
            linkedList3.add(Byte.valueOf((byte) sceneItem.getRelationValue()));
            String pattrenAJsonStr = sceneItem.getScene().getPattrenAJsonStr();
            if (!pattrenAJsonStr.equals("")) {
                i7 += i6;
                byte[] intToBytesSmallEndian = System_DataType_Util.intToBytesSmallEndian(i7);
                int length = intToBytesSmallEndian.length;
                int i9 = 0;
                while (i9 < length) {
                    Iterator it3 = it2;
                    linkedList2.add(Byte.valueOf(intToBytesSmallEndian[i9]));
                    i9++;
                    it2 = it3;
                }
                it = it2;
                List patternDatas = getPatternDatas(pattrenAJsonStr);
                linkedList4.addAll(patternDatas);
                i6 = patternDatas.size();
                if (GlobalConfig.deviceConfig.deviceType.equals(TF_FilesManager.TF1_FILE_DEVICETYPE)) {
                    sceneItem.getScene().getChannelByteList().set(3, Integer.valueOf(i));
                }
                i++;
            } else {
                it = it2;
            }
            String pattrenBJsonStr = sceneItem.getScene().getPattrenBJsonStr();
            if (!pattrenBJsonStr.equals("")) {
                i7 += i6;
                for (byte valueOf7 : System_DataType_Util.intToBytesSmallEndian(i7)) {
                    linkedList2.add(Byte.valueOf(valueOf7));
                }
                List patternDatas2 = getPatternDatas(pattrenBJsonStr);
                linkedList4.addAll(patternDatas2);
                int size4 = patternDatas2.size();
                if (GlobalConfig.deviceConfig.deviceType.equals(TF_FilesManager.TF1_FILE_DEVICETYPE)) {
                    sceneItem.getScene().getChannelByteList().set(20, Integer.valueOf(i));
                }
                i++;
                i6 = size4;
            }
            for (Integer intValue : sceneItem.getScene().getChannelByteList()) {
                linkedList3.add(Byte.valueOf((byte) intValue.intValue()));
            }
            progressBar2.setProgress(10 + (size3 * i8));
            it2 = it;
            i4 = 1;
        }
        linkedList.addAll(linkedList2);
        for (byte valueOf8 : System_DataType_Util.intToBytesSmallEndian(48 + linkedList2.size() + 4 + linkedList3.size() + linkedList4.size())) {
            linkedList.add(Byte.valueOf(valueOf8));
        }
        linkedList.addAll(linkedList3);
        linkedList.addAll(linkedList4);
        linkedList.add(Byte.valueOf(0));
        return System_DataType_Util.ByteListToByteArray(linkedList);
    }

    private List<Byte> getPatternDatas(String str) {
        try {
            return getPatternDatas(BaseFilesManager.getGraphicalList(new JSONArray(str), this.mCanvasScreen.width, this.mCanvasScreen.height));
        } catch (Exception unused) {
            return new ArrayList();
        }
    }

    private List<Byte> getPatternDatas(List<Graphical> list) {
        new ArrayList();
        if (GlobalConfig.deviceConfig.deviceType.equals(TF_FilesManager.TF1_FILE_DEVICETYPE)) {
            return this.patternDatasChangeManager.getPatternData_tf1(list);
        }
        return this.patternDatasChangeManager.getPatternData_tf2(list);
    }

    public List<byte[]> getSendSceneDatas(Scene scene) {
        ArrayList arrayList = new ArrayList();
        if (scene == null) {
            return arrayList;
        }
        arrayList.add(getDMXDataBytes(scene.getChannelByteList()));
        List arrayList2 = new ArrayList();
        if (!System_DataType_Util.isEmptyOrNull(scene.getPattrenAJsonStr())) {
            arrayList2 = getPatternDatas(scene.getPattrenAJsonStr());
        }
        List arrayList3 = new ArrayList();
        if (arrayList2.size() == 0) {
            if (System_DataType_Util.isEmptyOrNull(scene.getPattrenBJsonStr())) {
                return null;
            }
            arrayList3 = getPatternDatas(scene.getPattrenBJsonStr());
        } else if (!System_DataType_Util.isEmptyOrNull(scene.getPattrenBJsonStr()) && !scene.getPattrenAJsonStr().equals(scene.getPattrenBJsonStr())) {
            arrayList3 = getPatternDatas(scene.getPattrenBJsonStr());
        }
        byte[] sendPatternDataBytes = getSendPatternDataBytes(arrayList2, arrayList3);
        arrayList.add(getReadyPatternDataBytes(sendPatternDataBytes.length));
        arrayList.add(sendPatternDataBytes);
        return arrayList;
    }

    private byte[] getSendPatternDataBytes(List<Byte> list, List<Byte> list2) {
        short s;
        short s2;
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(6));
        arrayList.add(Byte.valueOf(1));
        arrayList.add(Byte.valueOf(90));
        if (list.size() > 0) {
            s2 = (short) (list.size() - 1);
            if (list2.size() > 0) {
                s = s2;
                s2 = (short) (list2.size() + s2);
                arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (s2 + 1 + 10)));
                arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(s));
                arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(s2));
                arrayList.addAll(list);
                arrayList.addAll(list2);
                return System_DataType_Util.ByteListToByteArray(arrayList);
            }
        } else {
            s2 = (short) (list2.size() - 1);
        }
        s = s2;
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (s2 + 1 + 10)));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(s));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(s2));
        arrayList.addAll(list);
        arrayList.addAll(list2);
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public List<byte[]> getSendPatternOrderDatas(List<Graphical> list) {
        if (list == null || list.size() == 0) {
            return null;
        }
        ArrayList arrayList = new ArrayList();
        byte[] sendPatternDataBytes = getSendPatternDataBytes(getPatternDatas(list));
        arrayList.add(getReadyPatternDataBytes(sendPatternDataBytes.length));
        arrayList.add(sendPatternDataBytes);
        return arrayList;
    }

    private byte[] getSendPatternDataBytes(List<Byte> list) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(6));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        short size = (short) (list.size() - 1);
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian((short) (list.size() + 10)));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(size));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(size));
        arrayList.addAll(list);
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    private byte[] getReadyPatternDataBytes(int i) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(5));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.addAll(System_DataType_Util.shortToByteListSamllEndian(8));
        byte[] shortToByteArraySamllEndian = System_DataType_Util.shortToByteArraySamllEndian((short) i);
        arrayList.add(Byte.valueOf(shortToByteArraySamllEndian[0]));
        arrayList.add(Byte.valueOf(shortToByteArraySamllEndian[1]));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] removeOutCachePatternsDatas(byte[] bArr, int i) {
        if (i < 32) {
            return null;
        }
        byte[] partBytes = System_DataType_Util.getPartBytes(bArr, 6, 7);
        byte[] partBytes2 = System_DataType_Util.getPartBytes(bArr, 8, 9);
        short byteToShort = System_DataType_Util.byteToShort(partBytes);
        if (byteToShort == System_DataType_Util.byteToShort(partBytes2)) {
            if (bArr.length <= i) {
                return bArr;
            }
            byte[] partBytes3 = System_DataType_Util.getPartBytes(bArr, i);
            byte[] shortToByteArraySamllEndian = System_DataType_Util.shortToByteArraySamllEndian((short) (i - 1));
            return System_DataType_Util.replacePartBytes(System_DataType_Util.replacePartBytes(partBytes3, shortToByteArraySamllEndian, 6), shortToByteArraySamllEndian, 8);
        } else if (bArr.length <= i) {
            return bArr;
        } else {
            if (i >= byteToShort + 10) {
                return System_DataType_Util.replacePartBytes(System_DataType_Util.getPartBytes(bArr, i), System_DataType_Util.shortToByteArraySamllEndian((short) (i - 1)), 8);
            }
            byte[] partBytes4 = System_DataType_Util.getPartBytes(bArr, i);
            byte[] shortToByteArraySamllEndian2 = System_DataType_Util.shortToByteArraySamllEndian((short) (i - 1));
            return System_DataType_Util.replacePartBytes(System_DataType_Util.replacePartBytes(partBytes4, shortToByteArraySamllEndian2, 6), shortToByteArraySamllEndian2, 8);
        }
    }

    public byte[] getDeviceParas() {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(7));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.add(Byte.valueOf(6));
        arrayList.add(Byte.valueOf(0));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] setDeviceParas(List<Byte> list) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(8));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.add(Byte.valueOf(31));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        for (Byte byteValue : list) {
            arrayList.add(Byte.valueOf(byteValue.byteValue()));
        }
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }

    public byte[] deleteTFFile(String str) {
        ArrayList arrayList = new ArrayList();
        arrayList.add(Byte.valueOf(-86));
        arrayList.add(Byte.valueOf(19));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(90));
        arrayList.add(Byte.valueOf(12));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        arrayList.add(Byte.valueOf(0));
        for (byte valueOf : str.getBytes()) {
            arrayList.add(Byte.valueOf(valueOf));
        }
        arrayList.add(Byte.valueOf(0));
        return System_DataType_Util.ByteListToByteArray(arrayList);
    }
}
