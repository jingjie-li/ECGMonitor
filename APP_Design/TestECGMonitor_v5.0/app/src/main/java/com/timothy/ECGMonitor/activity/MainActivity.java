package com.timothy.ECGMonitor.activity;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

import com.timothy.ECGMonitor.R;
import com.timothy.ECGMonitor.adapter.DeviceAdapter;
import com.timothy.ECGMonitor.entity.EntityDevice;
import com.timothy.ECGMonitor.service.BLEService;
import com.timothy.ECGMonitor.utils.BluetoothController;
import com.timothy.ECGMonitor.utils.ConstantUtils;
import com.timothy.ECGMonitor.ECG.EcgData;
import com.timothy.ECGMonitor.ECG.EcgDataAnalyzer;
import com.timothy.ECGMonitor.view.EcgView;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Message;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
/**
 * 主界面
 */
public class MainActivity extends Activity {
	private Button search;
	private ListView listview;
	private ArrayList<EntityDevice> list = new ArrayList<EntityDevice>();
	private DeviceAdapter adapter;
	private Intent intentService;
	private MsgReceiver receiver;
	
	private TextView connectedDevice;
	private TextView receivedMessage;

	////////////////////////////////////////////////////////////////////////////////////////////////

	private TextView beatRateText;
	private TextView rpeakValue;


	public android.os.Handler uiRefreshHandler = new android.os.Handler() {
		@Override
		public void handleMessage(Message msg) {
			switch (msg.what) {
				case 2:
					Log.d("handleMessage", "handleMessage: "+'2');
					ecgDataAnalyzer.beatRateAndRpeakDetection(new EcgData(msg.arg1, msg.arg2));
					break;
				case 3:
					Log.d("handleMessage", "handleMessage: "+'3');
					refreshList(0, msg.arg1);
					refreshList(1, msg.arg2);
					break;
				default:
					break;
			}
			super.handleMessage(msg);
		}
	};

	private EcgDataAnalyzer ecgDataAnalyzer = new EcgDataAnalyzer(uiRefreshHandler);

	private void refreshList(int listId, int refreshedData) {
		switch (listId) {
			case 0:
				beatRateText.setText("心 率: " + Integer.toString(refreshedData));
				break;
			case 1:
				rpeakValue.setText("RR间期: " + Double.toString(((double) refreshedData) / 100) + "s");
				break;
			default:
				break;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	//private EditText editSend;
	//private Button btnSend;
	BluetoothController controller=BluetoothController.getInstance();

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		initView();
		initService();
		initData();
		addListener();
		registerReceiver();

		//------------------//
		//loadDatas();
		//simulator();

		//------------//
		//DrawECG();
		
	}

	private void addListener() {
		listview.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int index,
					long arg3) {
				BluetoothController.getInstance().connect(list.get(index));
			}
		});
		
		search.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				list.clear();//清空上次的搜索结果
				connectedDevice.setText("");
				adapter.notifyDataSetChanged();
				if(!BluetoothController.getInstance().initBLE()){//手机不支持蓝牙
					Toast.makeText(MainActivity.this, "您的手机不支持蓝牙",
							Toast.LENGTH_SHORT).show();
					return;//手机不支持蓝牙就啥也不用干了，关电脑睡觉去吧
				}
				if (!BluetoothController.getInstance().isBleOpen()) {// 如果蓝牙还没有打开
					Toast.makeText(MainActivity.this, "请打开蓝牙",
							Toast.LENGTH_SHORT).show();
					return;
				}
				new GetDataTask().execute();// 搜索任务

			}
		});
		/*
		btnSend.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				String str=editSend.getText().toString();
				if(str!=null&&str.length()>0){
					controller.write(str.getBytes());
				}
				else {
					toast("请填上要发送的内容");
				}
				
			}
		});
		*/
	}

	private void initData() {
		adapter = new DeviceAdapter(this, list);
		listview.setAdapter(adapter);
	}

	/**
	 * 开始服务, 初始化蓝牙
	 */
	private void initService() {
		//开始服务
		intentService = new Intent(MainActivity.this,BLEService.class);   
		startService(intentService);
		// 初始化蓝牙
		BluetoothController.getInstance().initBLE();
	}

	/**
	 * findViewById
	 */
	private void initView() {
		connectedDevice=(TextView) findViewById(R.id.connected_device);
		receivedMessage=(TextView) findViewById(R.id.received_message);
		listview = (ListView) findViewById(R.id.list_devices);
		beatRateText = (TextView) findViewById(R.id.beat_rate);
		rpeakValue = (TextView) findViewById(R.id.RR_interval);

		//editSend=(EditText) findViewById(R.id.edit_send);
		//btnSend=(Button) findViewById(R.id.btn_send);
		search = (Button) findViewById(R.id.btn_search);
	}

	private void registerReceiver() {
		receiver=new MsgReceiver();
		IntentFilter intentFilter = new IntentFilter();
		intentFilter.addAction(ConstantUtils.ACTION_UPDATE_DEVICE_LIST);
		intentFilter.addAction(ConstantUtils.ACTION_CONNECTED_ONE_DEVICE);
		intentFilter.addAction(ConstantUtils.ACTION_RECEIVE_MESSAGE_FROM_DEVICE);
		intentFilter.addAction(ConstantUtils.ACTION_STOP_CONNECT);
		registerReceiver(receiver, intentFilter);
	}

	private class GetDataTask extends AsyncTask<Void, Void, String[]> {

		@Override
		protected String[] doInBackground(Void... params) {
			if(BluetoothController.getInstance().isBleOpen()){
				BluetoothController.getInstance().startScanBLE();
			};// 开始扫描
			return null;
		}

		@Override
		protected void onPostExecute(String[] result) {
			super.onPostExecute(result);
		}
	}

	/**
	 * 广播接收器
	 * 
	 */
	public Integer num = 0,counter = 0;
	private Integer receiveECGCounter = 0;
	public class MsgReceiver extends BroadcastReceiver {
		@Override
		public void onReceive(Context context, Intent intent) {
			if (intent.getAction().equalsIgnoreCase(
					ConstantUtils.ACTION_UPDATE_DEVICE_LIST)) {
				String name = intent.getStringExtra("name");
				String address = intent.getStringExtra("address");
				boolean found=false;//记录该条记录是否已在list中，
				for(EntityDevice device:list){
					if(device.getAddress().equals(address)){
						found=true;
						break;
						}
				}// for
				if(!found){
					EntityDevice temp = new EntityDevice();
					temp.setName(name);
					temp.setAddress(address);
					list.add(temp);
					adapter.notifyDataSetChanged();
				}
			}
			else if (intent.getAction().equalsIgnoreCase(ConstantUtils.ACTION_CONNECTED_ONE_DEVICE)){
				connectedDevice.setText("连接的蓝牙是："+intent.getStringExtra("address"));
			}
			
			else if (intent.getAction().equalsIgnoreCase(ConstantUtils.ACTION_STOP_CONNECT)){
				connectedDevice.setText("");
				toast("连接已断开");
			}
			
			else if (intent.getAction().equalsIgnoreCase(ConstantUtils.ACTION_RECEIVE_MESSAGE_FROM_DEVICE)){
				//receivedMessage.append("\n\r"+intent.getStringExtra("message"));
				String msg = intent.getStringExtra("message");
				long num = Long.parseLong(msg, 16);
				counter += 1;
				if(EcgView.isRunning) {
					try {
						Integer num1 = (int) num & 0x3FF;
						Integer num2 = (int) (num >> 10 ) & 0x3FF;
						Integer num3 = (int) (num >> 20 ) & 0x3FF;
						Integer num4 = (int) (num >> 30 ) & 0x3FF;
						Integer num5 = (int) (num >> 40 ) & 0x3FF;

						EcgView.addEcgData0(num5*4);
						EcgView.addEcgData0(num4*4);
						EcgView.addEcgData0(num3*4);
						EcgView.addEcgData0(num2*4);
						EcgView.addEcgData0(num1*4);
						Log.i("BLE", "onReceive: "+ counter.toString() + num3.toString()+num2.toString()+num1.toString());

						Message uiRefreshMessage1 = Message.obtain();
						Message uiRefreshMessage2 = Message.obtain();
						Message uiRefreshMessage3 = Message.obtain();
						Message uiRefreshMessage4 = Message.obtain();
						Message uiRefreshMessage5 = Message.obtain();

						uiRefreshMessage5.what = 2;
						uiRefreshMessage5.arg1 = num5*4;
						uiRefreshMessage5.arg2 = receiveECGCounter;
						uiRefreshHandler.sendMessage(uiRefreshMessage5);
						receiveECGCounter += 1;

						uiRefreshMessage4.what = 2;
						uiRefreshMessage4.arg1 = num4*4;
						uiRefreshMessage4.arg2 = receiveECGCounter;
						uiRefreshHandler.sendMessage(uiRefreshMessage4);
						receiveECGCounter += 1;

						uiRefreshMessage3.what = 2;
						uiRefreshMessage3.arg1 = num3*4;
						uiRefreshMessage3.arg2 = receiveECGCounter;
						uiRefreshHandler.sendMessage(uiRefreshMessage3);
						receiveECGCounter += 1;

						uiRefreshMessage2.what = 2;
						uiRefreshMessage2.arg1 = num2*4;
						uiRefreshMessage2.arg2 = receiveECGCounter;
						uiRefreshHandler.sendMessage(uiRefreshMessage2);
						receiveECGCounter += 1;

						uiRefreshMessage1.what = 2;
						uiRefreshMessage1.arg1 = num1*4;
						uiRefreshMessage1.arg2 = receiveECGCounter;
						uiRefreshHandler.sendMessage(uiRefreshMessage1);
						receiveECGCounter += 1;

						Log.i("BLE", "onReceive: "+receiveECGCounter.toString());
					} catch (Exception Ex) {
						Log.e("ttt", "Error: ", Ex);
					}
				}
				receivedMessage.setText(counter.toString() + ' ' +msg +" "+Long.toString(num)); //append("\n\r"+intent.getStringExtra("message"));
				receivedMessage.setMovementMethod(ScrollingMovementMethod.getInstance()) ;
			}
		}
	}
	
	
	private void toast(String str) {
		Toast.makeText(MainActivity.this, str, Toast.LENGTH_SHORT).show();
	}
	
	@Override
	protected void onDestroy() {
		super.onDestroy();
		stopService(intentService);
		unregisterReceiver(receiver);
	}

	//-----------------------------------------------------------//
	private List<Integer> datas = new ArrayList<Integer>();
	private List<Integer> data1Datas = new ArrayList<Integer>();

	private Queue<Integer> data0Q = new LinkedList<Integer>();
	private Queue<Integer> data1Q = new LinkedList<Integer>();

	private int flag = 0;

	//模拟心电发送，心电数据是一秒500个包，所以
	/*
	private void simulator(){
		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				if(EcgView.isRunning){
					EcgView.addEcgData0( num );
					//Log.i("simulator", "run: EcgView");
					/*
					int Add_N = 0;
					Log.i("ttt", "run Text: " + receivedMessage.getText());
					if (receivedMessage.getText() != "") {
						Add_N = (int) Double.parseDouble(receivedMessage.getText().toString());
						Log.i("ttt", "Num: "+Add_N);
					}
					EcgView.addEcgData0(Add_N);
					*/
					/*
					if(data0Q.size() > 0){
						int data = data0Q.poll();
						//Log.i("ttt", "EcgView data: "+data);
						EcgView.addEcgData0(data);
						//EcgView.addEcgData1(data1Q.poll());
					}
					//
				}

			}
		}, 0, 10);
	}
	*/

	private void loadDatas(){
		try{
			String data0 = "";
			InputStream in = getResources().openRawResource(R.raw.ecgdata);
			int length = in.available();
			byte [] buffer = new byte[length];
			in.read(buffer);
			data0 = new String(buffer);
			in.close();
			String[] data0s = data0.split(",");
			for(String str : data0s){
				datas.add(Integer.parseInt(str));
			}

			data0Q.addAll(datas);
			//data1Q.addAll(datas);
		}catch (Exception e){}

	}

	/*
	//////////////////////////////////////////
	private Paint paint;
	final int HEIGHT = 320;
	final int WIDTH = 768;
	final int X_OFFSET = 5;
	private int cx = X_OFFSET;
	// 实际的Y轴的位置
	int centerY = HEIGHT / 2;
	Timer timer = new Timer();
	TimerTask task = null;
	private SurfaceHolder surfaceHolder;

	private void DrawECG(){
		final SurfaceView SurView = (SurfaceView) findViewById(R.id.SurView);
		if(SurView==null){Log.i("ttt", "DrawECG: 0.1");return;}
		surfaceHolder = SurView.getHolder();
		if(surfaceHolder == null){Log.i("ttt", "DrawECG: 0.2");return;}
		Log.i("ttt", "DrawECG: 0.3");
		paint = new Paint();
		paint.setColor(Color.GREEN);
		paint.setStrokeWidth(3);
		Log.i("ttt", "DrawECG: 1");


		new Timer().schedule(new TimerTask() {
			@Override
			public void run() {
				if(drawBack(surfaceHolder)){
					this.cancel();
				}
			}
		}, 0, 20);

		cx = X_OFFSET;
		if(task != null)
		{
			task.cancel();
		}
		task = new TimerTask()
		{
			public void run()
			{
				try {
					int Add_N = 0;
					Log.i("ttt", "run Text: " + receivedMessage.getText());
					if (receivedMessage.getText() != "") {
						Add_N = (int) Double.parseDouble(receivedMessage.getText().toString());
						Log.i("ttt", "Num: "+Add_N);
					}else{return;}
					int cy = Add_N;
					Log.i("ttt", "run cy: "+cy);
					Canvas canvas = surfaceHolder.lockCanvas(new Rect(cx, cy - 2, cx + 2, cy + 2));
					canvas.drawColor(Color.WHITE);
					canvas.drawPoint(cx, cy, paint);
					cx++;
					if (cx > WIDTH) {
						cx = cx - WIDTH;
					}
					surfaceHolder.unlockCanvasAndPost(canvas);
				}catch(Exception e1){
					Log.e("ttt", "Error: ",e1 );
				}
			}
		};
		timer.schedule(task , 0 , 30);

		surfaceHolder.addCallback(new Callback()
		{
			@Override
			public void surfaceChanged(SurfaceHolder surfaceHolder, int format,
									   int width, int height)
			{
				drawBack(surfaceHolder);
			}
			@Override
			public void surfaceCreated(final SurfaceHolder myHolder){ }
			@Override
			public void surfaceDestroyed(SurfaceHolder surfaceHolder)
			{
				timer.cancel();
			}
		});

	}

	private boolean drawBack(SurfaceHolder holder)
	{
		Log.i("ttt", "DrawECG: drawBack");
		Canvas canvas = holder.lockCanvas();
		if(canvas == null){return false;}
		// 绘制白色背景
		canvas.drawColor(Color.WHITE);
		Paint p = new Paint();
		p.setColor(Color.BLACK);
		p.setStrokeWidth(2);
		// 绘制坐标轴
		canvas.drawLine(X_OFFSET , centerY , WIDTH , centerY , p);
		canvas.drawLine(X_OFFSET , 40 , X_OFFSET , HEIGHT , p);
		holder.unlockCanvasAndPost(canvas);
		holder.lockCanvas(new Rect(0 , 0 , 0 , 0));
		holder.unlockCanvasAndPost(canvas);
		return true;
	}
	*/
}
