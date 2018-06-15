package com.timothy.ECGMonitor.utils;

import java.util.Iterator;
import java.util.List;

import com.timothy.ECGMonitor.App;
import com.timothy.ECGMonitor.entity.EntityDevice;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

/**
 * 蓝牙控制类
 * 
 * @author wangdandan
 * 
 */
public class BluetoothController {
	private String deviceAddress;
	private String deviceName;

	private BluetoothAdapter bleAdapter;
	private Handler serviceHandler;// 服务句柄

	static BluetoothGatt bleGatt;// 连接
	static BluetoothGattCharacteristic bleGattCharacteristic;

	/**
	 * 单例模式
	 */
	private static BluetoothController instance = null;

	private BluetoothController() {
	}

	public static BluetoothController getInstance() {
		if (instance == null)
			instance = new BluetoothController();
		return instance;
	}

	/**
	 * 初始化蓝牙
	 * 
	 * @return
	 */
	public boolean initBLE() {
		// 检查当前手机是否支持ble 蓝牙,如果不支持退出程序
		// App.app可能会报错，清单文件中不要忘了配置application
		if (!App.app.getPackageManager().hasSystemFeature(
				PackageManager.FEATURE_BLUETOOTH_LE)) {
			return false;
		}
		// 初始化 Bluetooth adapter, 通过蓝牙管理器得到一个参考蓝牙适配器(API必须在以上android4.3或以上版本)
		final BluetoothManager bluetoothManager = (BluetoothManager) App.app
				.getSystemService(Context.BLUETOOTH_SERVICE);
		bleAdapter = bluetoothManager.getAdapter();
		// 检查设备上是否支持蓝牙
		if (bleAdapter == null)
			return false;
		else
			return true;
	}

	/**
	 * 设置服务事件接收者
	 * 
	 * @return
	 */
	public void setServiceHandler(Handler handler) {
		// handler初始化在service中，用于逻辑和界面的沟通
		serviceHandler = handler;
	}

	/**
	 * 搜索蓝牙回调
	 */
	BluetoothAdapter.LeScanCallback bleScanCallback = new BluetoothAdapter.LeScanCallback() {
		@Override
		public void onLeScan(BluetoothDevice device, int arg1, byte[] arg2) {
			// device就是搜索到的设备
			String name = device.getName();
			if (name == null)
				return;
			if (BluetoothController.this.serviceHandler != null
					&& !name.isEmpty()) {
				Message msg = new Message();
				msg.what = ConstantUtils.WM_UPDATE_BLE_LIST;
				msg.obj = device;
				BluetoothController.this.serviceHandler.sendMessage(msg);
			}
		}
	};

	/**
	 * 开始扫描蓝牙
	 */
	public void startScanBLE() {
		bleAdapter.startLeScan(bleScanCallback);
		if (serviceHandler != null)
			serviceHandler.sendEmptyMessageDelayed(
					ConstantUtils.WM_STOP_SCAN_BLE, 5000);
	}

	/**
	 * 停止扫描蓝牙设备
	 */
	public void stopScanBLE() {
		bleAdapter.stopLeScan(bleScanCallback);
	}

	/**
	 * 是否蓝牙打开
	 * 
	 * @return
	 */
	public boolean isBleOpen() {
		return bleAdapter.isEnabled();
	}

	/**
	 * 连接蓝牙设备
	 * 
	 * @param device
	 *            待连接的设备
	 */
	public void connect(EntityDevice device) {
		deviceAddress = device.getAddress();
		deviceName = device.getName();
		BluetoothDevice localBluetoothDevice = bleAdapter
				.getRemoteDevice(device.getAddress());
		if (bleGatt != null) {

			bleGatt.disconnect();
			bleGatt.close();
			bleGatt = null;
		}
		bleGatt = localBluetoothDevice.connectGatt(App.app, false,
				bleGattCallback);
	}

	/**
	 * 与蓝牙通信回调
	 */
	public BluetoothGattCallback bleGattCallback = new BluetoothGattCallback() {
		/**
		 * 收到消息
		 */
		public void onCharacteristicChanged(
				BluetoothGatt paramAnonymousBluetoothGatt,
				BluetoothGattCharacteristic paramAnonymousBluetoothGattCharacteristic) {

			byte[] arrayOfByte = paramAnonymousBluetoothGattCharacteristic
					.getValue();
			if (BluetoothController.this.serviceHandler != null) {
				Message msg = new Message();
				msg.what = ConstantUtils.WM_RECEIVE_MSG_FROM_BLE;
				// byte数组转换为十六进制字符串
				msg.obj = ConvertUtils.getInstance().bytesToHexString(
						arrayOfByte);
				BluetoothController.this.serviceHandler.sendMessage(msg);
			}
			// 也可以先打印出来看看
			Log.i("TEST",
					ConvertUtils.getInstance().bytesToHexString(arrayOfByte));
		}

		public void onCharacteristicRead(
				BluetoothGatt paramAnonymousBluetoothGatt,
				BluetoothGattCharacteristic paramAnonymousBluetoothGattCharacteristic,
				int paramAnonymousInt) {
		}

		public void onCharacteristicWrite(
				BluetoothGatt paramAnonymousBluetoothGatt,
				BluetoothGattCharacteristic paramAnonymousBluetoothGattCharacteristic,
				int paramAnonymousInt) {
		}

		/**
		 * 连接状态改变
		 */
		public void onConnectionStateChange(
				BluetoothGatt paramAnonymousBluetoothGatt, int oldStatus,
				int newStatus) {
			if (newStatus == 2)// 已连接状态，表明连接成功
			{
				Message msg = new Message();
				msg.what = ConstantUtils.WM_BLE_CONNECTED_STATE_CHANGE;
				Bundle bundle = new Bundle();
				bundle.putString("address", deviceAddress);
				bundle.putString("name", deviceName);
				msg.obj = bundle;
				serviceHandler.sendMessage(msg);
				paramAnonymousBluetoothGatt.discoverServices();
				// 连接到蓝牙后查找可以读写的服务，蓝牙有很多服务
				return;
			}
			if (newStatus == 0)// 断开连接或未连接成功
			{
				serviceHandler.sendEmptyMessage(ConstantUtils.WM_STOP_CONNECT);
				return;
			}
			paramAnonymousBluetoothGatt.disconnect();
			paramAnonymousBluetoothGatt.close();
			return;
		}

		public void onDescriptorRead(BluetoothGatt paramAnonymousBluetoothGatt,
				BluetoothGattDescriptor paramAnonymousBluetoothGattDescriptor,
				int paramAnonymousInt) {
		}

		public void onDescriptorWrite(
				BluetoothGatt paramAnonymousBluetoothGatt,
				BluetoothGattDescriptor paramAnonymousBluetoothGattDescriptor,
				int paramAnonymousInt) {
		}

		public void onReadRemoteRssi(BluetoothGatt paramAnonymousBluetoothGatt,
				int paramAnonymousInt1, int paramAnonymousInt2) {
		}

		public void onReliableWriteCompleted(
				BluetoothGatt paramAnonymousBluetoothGatt, int paramAnonymousInt) {
		}

		public void onServicesDiscovered(
				BluetoothGatt paramAnonymousBluetoothGatt, int paramAnonymousInt) {
			BluetoothController.this.findService(paramAnonymousBluetoothGatt
					.getServices());
		}

	};

	/**
	 * 传输数据
	 * 
	 * @param byteArray
	 * @return
	 */
	public boolean write(byte byteArray[]) {
		if (bleGattCharacteristic == null)
			return false;
		if (bleGatt == null)
			return false;
		bleGattCharacteristic.setValue(byteArray);
		return bleGatt.writeCharacteristic(bleGattCharacteristic);
	}

	/**
	 * 传输数据
	 * 
	 * @param str
	 * @return
	 */
	public boolean write(String str) {
		if (bleGattCharacteristic == null)
			return false;
		if (bleGatt == null)
			return false;
		bleGattCharacteristic.setValue(str);
		return bleGatt.writeCharacteristic(bleGattCharacteristic);
	}

	/**
	 * 搜索服务
	 * 
	 * @param paramList
	 */
	public void findService(List<BluetoothGattService> paramList) {

		Iterator localIterator1 = paramList.iterator();
		while (localIterator1.hasNext()) {
			BluetoothGattService localBluetoothGattService = (BluetoothGattService) localIterator1
					.next();
			if (localBluetoothGattService.getUuid().toString()
					.equalsIgnoreCase(ConstantUtils.UUID_SERVER)) {
				List localList = localBluetoothGattService.getCharacteristics();
				Iterator localIterator2 = localList.iterator();
				while (localIterator2.hasNext()) {
					BluetoothGattCharacteristic localBluetoothGattCharacteristic = (BluetoothGattCharacteristic) localIterator2
							.next();
					if (localBluetoothGattCharacteristic.getUuid().toString()
							.equalsIgnoreCase(ConstantUtils.UUID_NOTIFY)) {
						bleGattCharacteristic = localBluetoothGattCharacteristic;
						break;
					}
				}
				break;
			}

		}

		bleGatt.setCharacteristicNotification(bleGattCharacteristic, true);
	}

}
