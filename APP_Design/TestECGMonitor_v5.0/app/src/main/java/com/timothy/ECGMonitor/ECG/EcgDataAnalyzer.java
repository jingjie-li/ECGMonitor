package com.timothy.ECGMonitor.ECG;

import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class EcgDataAnalyzer {

    private Handler uiRefreshHandler;
    private Integer NumForAna = 25;
    public double beatRate = 0;
    private double lastAvgValue = 0;
    DataTemp[] peakDetectionDataTemp = new DataTemp[NumForAna];
    private boolean ifFirstRpeakDetected = false;
    private DataTemp rpeakLocalMax = new DataTemp(0, 0);
    private DataTemp rpeakMaxTemp = new DataTemp(0, 0);
    private DataTemp rpeak = new DataTemp(0, 0);
    private DataTemp lastRpeak = new DataTemp(0, 0);

    private class DataTemp {
        private double data;
        private int dataId;

        public DataTemp(int data, int dataId) {
            this.data = (double) data;
            this.dataId = dataId;
        }

        public DataTemp() {

        }

        public synchronized double getData() {
            return data;
        }

        public int getDataId() {
            return dataId;
        }

        public synchronized void setData(double data) {
            this.data = data;
        }
    }

    private static final String TAG = "ANA";
    private class BeatRateAndRpeakDetectionThread extends Thread {

        DataTemp[] dataTemp = new DataTemp[NumForAna];

        public BeatRateAndRpeakDetectionThread() {
            int cnt;
            for (cnt = 0; cnt < NumForAna; cnt++) {
                dataTemp[cnt] = peakDetectionDataTemp[cnt];
            }
        }

        @Override
        public void run() {
            super.run();
            int cnt;
            double dataAvgValue = 0;
            Log.i(TAG , "run: "+dataTemp.length);
            for (cnt = 0;cnt < NumForAna;cnt++){
                Log.i(TAG , "run: "+Integer.toString(cnt)+" "+Double.toString(dataTemp[cnt].getData()));
            }
            for (cnt = 5; cnt < NumForAna-4; cnt++) {
                dataTemp[cnt].setData(dataTemp[cnt - 5].getData() +
                        dataTemp[cnt - 4].getData() + dataTemp[cnt - 3].getData() +
                        dataTemp[cnt - 2].getData() + dataTemp[cnt - 1].getData() +
                        dataTemp[cnt].getData() + dataTemp[cnt + 1].getData() +
                        dataTemp[cnt + 2].getData() + dataTemp[cnt + 3].getData() +
                        dataTemp[cnt + 4].getData());
                dataTemp[cnt].setData(dataTemp[cnt].getData() / 10);
            }
            rpeakLocalMax = dataTemp[0];
            for (cnt = 0; cnt < NumForAna; cnt++) {
                dataAvgValue += dataTemp[cnt].getData();
                if (rpeakLocalMax.getData() < dataTemp[cnt].getData()) {
                    rpeakLocalMax = dataTemp[cnt];
                }
            }
            dataAvgValue = dataAvgValue / NumForAna;

            if (ifFirstRpeakDetected) {
                if ((Math.abs((rpeakMaxTemp.getData() - lastAvgValue) /
                        (rpeakLocalMax.getData() - dataAvgValue) - 1) < 0.5)
                        &&
                        ((rpeakLocalMax.getDataId() - rpeakMaxTemp.getDataId()) > 60)) {
                    rpeakMaxTemp = rpeakLocalMax;
                    lastAvgValue = dataAvgValue;
                    Log.i(TAG, "hit"+ Double.toString(rpeakMaxTemp.getData()));
                    rpeaksHandling(rpeakMaxTemp);
                }
            } else {
                if (rpeakMaxTemp.getData() < rpeakLocalMax.getData()) {
                    rpeakMaxTemp = rpeakLocalMax;
                    lastAvgValue = dataAvgValue;
                }
                if ((dataTemp[0].getDataId() > 200) && ((rpeakMaxTemp.getData() / Math.abs(dataAvgValue)) > 1.1)) {
                    Log.i(TAG, "get first"+Double.toString(rpeakMaxTemp.getData()));
                    ifFirstRpeakDetected = true;
                    lastRpeak = rpeakMaxTemp;
                }
            }
        }
    }

    public EcgDataAnalyzer(Handler handler) {
        uiRefreshHandler = handler;
    }

    public void beatRateAndRpeakDetection(EcgData ecgData) {

        Log.i(TAG, "beatRateAndRpeakDetection: Value "+Integer.toString(ecgData.getValueInInt()) + " Id "+Integer.toString(ecgData.getDataId()));
        int numberInTemp = (ecgData.getDataId() + 1) % NumForAna;
        Log.i(TAG, "beatRateAndRpeakDetection: "+Integer.toString(numberInTemp));
        if (numberInTemp == 0) {
            DataTemp dataTemp = new DataTemp(ecgData.getValueInInt(), ecgData.getDataId());
            peakDetectionDataTemp[NumForAna-1] = dataTemp;
            BeatRateAndRpeakDetectionThread beatRateAndRpeakDetectionThread
                    = new BeatRateAndRpeakDetectionThread();
            beatRateAndRpeakDetectionThread.start();
        } else {
            DataTemp dataTemp = new DataTemp(ecgData.getValueInInt(), ecgData.getDataId());
            peakDetectionDataTemp[numberInTemp - 1] = dataTemp;
        }
    }

    public void rpeaksHandling(DataTemp recentRpeak) {
        if (ifFirstRpeakDetected) {
            double RRinterval = (recentRpeak.getDataId() - lastRpeak.getDataId()) * EcgData.getRECORDRATE();
            beatRate = 60 / RRinterval;
            lastRpeak = recentRpeak;
            Message uiRefreshMessage = Message.obtain();
            uiRefreshMessage.what = 3;
            uiRefreshMessage.arg1 = (int) beatRate;
            uiRefreshMessage.arg2 = (int) (RRinterval*100);
            uiRefreshHandler.sendMessage(uiRefreshMessage);
        } else {
            lastRpeak = recentRpeak;
        }
    }
}
