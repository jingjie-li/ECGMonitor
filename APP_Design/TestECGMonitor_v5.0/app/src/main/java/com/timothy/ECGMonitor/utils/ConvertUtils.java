package com.timothy.ECGMonitor.utils;

import android.util.Log;

public class ConvertUtils {

	/**
	 * 单例模式
	 */
	static ConvertUtils instance = null;// 句柄

	private ConvertUtils() {
	}

	public static ConvertUtils getInstance() {
		if (instance == null)
			instance = new ConvertUtils();
		return instance;
	}

	/**
	 * byte数组转换为十六进制字符串
	 * 
	 * @param b
	 * @return
	 */
	public String bytesToHexString(byte[] b) {
		if (b.length == 0) {
			return null;
		}
		StringBuilder sb = new StringBuilder("");
		for (int i = 0; i < b.length; i++) {
			Log.i("testByte", "bytesToHexString: "+b.length);
			int value = b[i] & 0xFF; // 按位与运算，都是1时结果为1，其它为0，所以与全是1相与，结果还是原来的01串
			String hv = Integer.toHexString(value);
			if (hv.length() < 2) {
				sb.append(0);
			}

			sb.append(hv);
		}
		return sb.toString();
	}
}
