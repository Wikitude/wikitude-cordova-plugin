package com.wikitude.phonegap;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Date;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.content.ContentValues;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Rect;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.media.AudioManager;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.provider.MediaStore.Images;
import android.text.format.DateUtils;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewManager;
import android.view.inputmethod.InputMethodManager;
import android.widget.Toast;

import com.wikitude.architect.ArchitectView;
import com.wikitude.architect.ArchitectView.ArchitectUrlListener;
import com.wikitude.architect.ArchitectView.CaptureScreenCallback;
import com.wikitude.architect.StartupConfiguration;
import com.wikitude.architect.StartupConfiguration.CameraPosition;
import com.wikitude.phonegap.WikitudePlugin.ArchitectViewPhoneGap.OnKeyUpDownListener;



/**
 * Basic PhoneGap Wikitude ARchitect Plugin
 * 
 * You must add "<plugin name="WikitudePlugin" value="com.wikitude.phonegap.WikitudePlugin"/>"
 * in config.xml to enable this plug-in in your project
 * 
 * Also ensure to have wikitudesdk.jar in your libs folder
 * 
 * Note:
 * This plug-in is written under Apache License, Version 2.0
 * http://www.apache.org/licenses/LICENSE-2.0.html
 */
public class WikitudePlugin extends CordovaPlugin implements ArchitectUrlListener {

	/** PhoneGap-root to Android-app-assets folder ; e.g. use "assets/foo.html" as source if you want to load foo.html from your android-project's assets-folder */
	private static final String	LOCAL_ASSETS_PATH_ROOT		= "assets/";


	/* static action strings */
	/**
	 * opens architect-view (add to view stack)
	 */
	private static final String	ACTION_OPEN					= "open";

	/**
	 * closes architect-view (remove view stack)
	 */
	private static final String	ACTION_CLOSE				= "close";

	/**
	 * set visibility of architectView to visible (of present)
	 */
	private static final String	ACTION_SHOW					= "show";

	/**
	 * set visibility of architectView to invisible (of present)
	 */
	private static final String	ACTION_HIDE					= "hide";

	/**
	 * inject location information
	 */
	private static final String	ACTION_SET_LOCATION			= "setLocation";
	
	/**
	 * inject location information
	 */
	private static final String	ACTION_CAPTURE_SCREEN			= "captureScreen";

	/**
	 * callback for uri-invocations
	 */
	private static final String	ACTION_ON_URLINVOKE			= "onUrlInvoke";

	/**
	 * life-cycle notification for resume
	 */
	private static final String	ACTION_ON_RESUME			= "onResume";

	/**
	 * life-cycle notification for pause
	 */
	private static final String	ACTION_ON_PAUSE				= "onPause";

	/**
	 * check if view is on view-stack (no matter if visible or not)
	 */
	private static final String	ACTION_STATE_ISOPEN			= "isOpen";

	/**
	 * opens architect-view (add to view stack)
	 */
	private static final String	ACTION_IS_DEVICE_SUPPORTED	= "isDeviceSupported";

	/**
	 * check if view is on view-stack (no matter if visible or not)
	 */
	private static final String	ACTION_CALL_JAVASCRIPT		= "callJavascript";

	/**
	 * the Wikitude ARchitectview
	 */
	private ArchitectViewPhoneGap		architectView;

	/**
	 * callback-Id of url-invocation method
	 */
	private CallbackContext		urlInvokeCallback			= null;

	/**
	 * callback-id of "open"-action method
	 */
	private CallbackContext		openCallback				= null;
	
	/**
	 * last known location of the user, used internally for content-loading after user location was fetched
	 */
	protected Location lastKnownLocaton;
	

	/**
	 * sample location strategy
	 */
	protected ILocationProvider				locationProvider;
	
	
	/**
	 * location listener receives location updates and must forward them to the architectView
	 */
	protected LocationListener locationListener;
	
	private boolean useCustomLocation						= false;
	

	@Override
	public boolean execute( final String action, final JSONArray args, final CallbackContext callContext ) {

		/* hide architect-view -> destroy and remove from activity */
		if ( WikitudePlugin.ACTION_CLOSE.equals( action ) ) {
			if ( this.architectView != null ) {
				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						removeArchitectView();
					}
				} );
				callContext.success( action + ": architectView is present" );
			}
			else {
				callContext.error( action + ": architectView is not present" );
			}
			return true;
		}

		/* return success only if view is opened (no matter if visible or not) */
		if ( WikitudePlugin.ACTION_STATE_ISOPEN.equals( action ) ) {
			if ( this.architectView != null ) {
				callContext.success( action + ": architectView is present" );
			} else {
				callContext.error( action + ": architectView is not present" );
			}
			return true;
		}

		/* return success only if view is opened (no matter if visible or not) */
		if ( WikitudePlugin.ACTION_IS_DEVICE_SUPPORTED.equals( action ) ) {
			JSONArray jsonArray = null;
			try {
				jsonArray = args.getJSONArray( 0 );
			} catch (JSONException e) {
			}
			int featuresBitMap = convertArFeatures(jsonArray);
			if ( (ArchitectView.getSupportedFeaturesForDevice( this.cordova.getActivity() ) & featuresBitMap) == featuresBitMap ) {
				callContext.success("This device is supported" );
			} else {
				callContext.error("This device is NOT supported" );
			}
			return true;
		}
		
		if (WikitudePlugin.ACTION_CAPTURE_SCREEN.equals(action) ) {
			if (architectView!=null) {

				int captureMode = ArchitectView.CaptureScreenCallback.CAPTURE_MODE_CAM_AND_WEBVIEW;

				try {
					captureMode = ( args.getBoolean( 0 )) ? ArchitectView.CaptureScreenCallback.CAPTURE_MODE_CAM_AND_WEBVIEW : ArchitectView.CaptureScreenCallback.CAPTURE_MODE_CAM;
					
				} catch (Exception e) {
					// unexpected error;
				}
				String name = "";
				if (args.length() > 1 && !args.isNull(1)) {
					try {
		 				name = args.getString(1);
					} catch (final Exception e) {
						e.printStackTrace();
					}
				}

				final String fileName = name;
				
				architectView.captureScreen(captureMode, new CaptureScreenCallback() {
					
					@Override
					public void onScreenCaptured(Bitmap screenCapture) {
						final File screenCaptureFile;
						final String name = System.currentTimeMillis() + ".jpg";
						try {
							if (fileName.equals("")) {
 								final File imageDirectory = Environment.getExternalStorageDirectory();
								if (imageDirectory == null) {
									callContext.error("External storage not available");
								}
								screenCaptureFile = new File (imageDirectory, name);
							} else {
								File screenCapturePath = new File (fileName);
								if (screenCapturePath.isDirectory()) {
									screenCaptureFile = new File (screenCapturePath, name);
								} else { 
									screenCaptureFile = screenCapturePath;
								}
							}
							if (screenCaptureFile.exists()) {
								screenCaptureFile.delete();
							}
							final FileOutputStream out = new FileOutputStream(screenCaptureFile);
							screenCapture.compress(Bitmap.CompressFormat.JPEG, 90, out);
							out.flush();
							out.close();
							
							ContentValues values = new ContentValues();
						    values.put(Images.Media.DATE_TAKEN, System.currentTimeMillis());
						    values.put(Images.Media.MIME_TYPE, "image/jpeg");
						    values.put(MediaStore.MediaColumns.DATA, screenCaptureFile.getAbsolutePath());

						    Context context= cordova.getActivity().getApplicationContext();
						    context.getContentResolver().insert(Images.Media.EXTERNAL_CONTENT_URI, values);
							
							cordova.getActivity().runOnUiThread(new Runnable() {
								
								@Override
								public void run() {
									final String absoluteCaptureImagePath = screenCaptureFile.getAbsolutePath();
									callContext.success(absoluteCaptureImagePath);
									
// 								in case you want to sent the pic to other applications, uncomment these lines (for future use)
//								final Intent share = new Intent(Intent.ACTION_SEND);
//								share.setType("image/jpg");
//								share.putExtra(Intent.EXTRA_STREAM, Uri.fromFile(screenCaptureFile));
//								final String chooserTitle = "Share Snaphot";
//								cordova.getActivity().startActivity(Intent.createChooser(share, chooserTitle));
								}
							});
						} catch (Exception e) {
							callContext.error(e.getMessage());
						}
						
					}
				});
				return true;
			}
		}



		/* life-cycle's RESUME */
		if ( WikitudePlugin.ACTION_ON_RESUME.equals( action ) ) {

			if ( this.architectView != null ) {
				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						WikitudePlugin.this.architectView.onResume();
						callContext.success( action + ": architectView is present" );
						if (locationProvider != null) {
							locationProvider.onResume();
						}
					}
				} );

				// callContext.success( action + ": architectView is present" );
			} else {
				callContext.error( action + ": architectView is not present" );
			}
			return true;
		}

		/* life-cycle's PAUSE */
		if ( WikitudePlugin.ACTION_ON_PAUSE.equals( action ) ) {
			if ( architectView != null ) {
				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						WikitudePlugin.this.architectView.onPause();
						if (locationProvider != null) {
							locationProvider.onPause();
						}
					}
				} );

				callContext.success( action + ": architectView is present" );
			} else {
				callContext.error( action + ": architectView is not present" );
			}
			return true;
		}

		/* set visibility to "visible", return error if view is null */
		if ( WikitudePlugin.ACTION_SHOW.equals( action ) ) {

			this.cordova.getActivity().runOnUiThread( new Runnable() {

				@Override
				public void run() {
					if ( architectView != null ) {
						architectView.setVisibility( View.VISIBLE );
						callContext.success( action + ": architectView is present" );
					} else {
						callContext.error( action + ": architectView is not present" );
					}
				}
			} );


			return true;
		}

		/* set visibility to "invisible", return error if view is null */
		if ( WikitudePlugin.ACTION_HIDE.equals( action ) ) {

			this.cordova.getActivity().runOnUiThread( new Runnable() {

				@Override
				public void run() {
					if ( architectView != null ) {
						architectView.setVisibility( View.INVISIBLE );
						callContext.success( action + ": architectView is present" );
					} else {
						callContext.error( action + ": architectView is not present" );
					}
				}
			} );

			return true;
		}

		/* define call-back for url-invocations */
		if ( WikitudePlugin.ACTION_ON_URLINVOKE.equals( action ) ) {
			this.urlInvokeCallback = callContext;
			final PluginResult result = new PluginResult( PluginResult.Status.NO_RESULT, action + ": registered callback" );
			result.setKeepCallback( true );
			callContext.sendPluginResult( result );
			return true;
		}

		/* location update */
		if ( WikitudePlugin.ACTION_SET_LOCATION.equals( action ) ) {
			if ( this.architectView != null ) {
				try {
					final double lat = args.getDouble( 0 );
					final double lon = args.getDouble( 1 );
					float alt = Float.MIN_VALUE;
					try {
						alt = (float)args.getDouble( 2 );
					} catch ( Exception e ) {
						// invalid altitude -> ignore it
					}
					final float altitude = alt;
					Double acc = null;
					try {
						acc = args.getDouble( 3 );
					} catch ( Exception e ) {
						// invalid accuracy -> ignore it
					}
					final Double accuracy = acc;
					if ( this.cordova != null && this.cordova.getActivity() != null ) {
						this.useCustomLocation = true;
						cordova.getActivity().runOnUiThread(
//						this.cordova.getThreadPool().execute( 
								new Runnable() {

							@Override
							public void run() {
								if ( accuracy != null ) {
									WikitudePlugin.this.architectView.setLocation( lat, lon, altitude, accuracy.floatValue() );
								} else {
									WikitudePlugin.this.architectView.setLocation( lat, lon, altitude );
								}
							}
						} );
					}

				} catch ( Exception e ) {
					callContext.error( action + ": exception thrown, " + e != null ? e.getMessage() : "(exception is NULL)" );
					return true;
				}
				callContext.success( action + ": updated location" );
				return true;
			} else {
				/* return error if there is no architect-view active*/
				callContext.error( action + ": architectView is not present" );
			}
			return true;
		}

		if ( WikitudePlugin.ACTION_CALL_JAVASCRIPT.equals( action ) ) {

			String logMsg = null;
			try {
				final String callJS = args.getString( 0 );
				logMsg = callJS;

				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						if ( architectView != null ) {
							WikitudePlugin.this.architectView.callJavascript( callJS );
						} else {
							callContext.error( action + ": architectView is not present" );
						}
					}
				} );

			} catch ( JSONException je ) {
				callContext.error( action + ": exception thrown, " + je != null ? je.getMessage() : "(exception is NULL)" );
				return true;
			}
			callContext.success( action + ": called js, '" + logMsg + "'" );

			return true;
		}


		/* initial set-up, show ArchitectView full-screen in current screen/activity */
		if ( WikitudePlugin.ACTION_OPEN.equals( action ) ) {
			this.openCallback = callContext;
			PluginResult result = null;
			try {
				final JSONObject params = args.getJSONObject( 0 );
				final String apiKey = params.getString( "SDKKey" );
				final String filePath = params.getString( "ARchitectWorldURL" );
				int featuresTmp = 0;
				
				try {
					final JSONArray jsonArray = params.getJSONArray( "RequiredFeatures" );
					featuresTmp = convertArFeatures(jsonArray);
				} catch (JSONException e) {
					featuresTmp = StartupConfiguration.Features.Geo | StartupConfiguration.Features.Tracking2D;
				}
				final int features = featuresTmp;
				
				JSONObject startupConfigurationTmp;
				try {
					startupConfigurationTmp = params.getJSONObject( "StartupConfiguration" );
				} catch (Exception e) {
					startupConfigurationTmp = null;
				}
				final JSONObject startupConfiguration = startupConfigurationTmp;
				
				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						try {
							WikitudePlugin.this.addArchitectView( apiKey, filePath, features, startupConfiguration );

							/* call success method once architectView was added successfully */
							if ( openCallback != null ) {
								PluginResult result = new PluginResult( PluginResult.Status.OK );
								result.setKeepCallback( false );
								openCallback.sendPluginResult( result );
							}
						} catch ( Exception e ) {
							/* in case "addArchitectView" threw an exception -> notify callback method asynchronously */
							openCallback.error( e != null ? e.getMessage() : "Exception is 'null'" );
						}
					}
				} );

			} catch ( Exception e ) {
				result = new PluginResult( PluginResult.Status.ERROR, action + ": exception thown, " + e != null ? e.getMessage() : "(exception is NULL)" );
				result.setKeepCallback( false );
				callContext.sendPluginResult( result );
				return true;
			}

			/* adding architect-view is done in separate thread, ensure to setKeepCallback so one can call success-method properly later on */
			result = new PluginResult( PluginResult.Status.NO_RESULT, action + ": no result required, just registered callback-method" );
			result.setKeepCallback( true );
			callContext.sendPluginResult( result );
			return true;
		}

		/* fall-back return value */
		callContext.sendPluginResult( new PluginResult( PluginResult.Status.ERROR, "no such action: " + action ) );
		return false;
	}

	/**
	 * called when url was invoked in architectView (by e.g. calling document.location = "myprotocoll://foo";
	 * @param url the invoked url (e.g. "architectsdk://foo")
	 * @return true if call was handled properly
	 */
	@Override
	public boolean urlWasInvoked( final String url ) {

		/* call callback-method if set*/
		if ( this.urlInvokeCallback != null ) {
			try {
				/* pass called url as String to callback-method */
				final PluginResult res = new PluginResult( PluginResult.Status.OK, url );
				res.setKeepCallback( true );
				this.urlInvokeCallback.sendPluginResult( res );
			} catch ( Exception e ) {
				this.urlInvokeCallback.error( "invalid url invoked: " + url );
			}
			return true;
		}
		return false;
	}

	/**
	 * hides/removes ARchitect-View completely
	 * @return true if successful, false otherwise
	 */
	private boolean removeArchitectView() {
		if ( this.architectView != null ) {
						
			/* fake life-cycle calls, because activity is already up and running */
			this.architectView.onPause();
			this.architectView.onDestroy();

			// clean-up used temp-directory
			try {
				WikitudePlugin.clearCacheFolder( new File( ArchitectView.getCacheDirectoryAbsoluteFilePath( this.cordova.getActivity() ) ), 0 );
			} catch ( Exception e ) {
				// had troubles in clearing files from cache
				e.printStackTrace();
			}

			this.architectView.setVisibility( View.GONE );
			((ViewManager)this.architectView.getParent()).removeView( this.architectView );
			this.architectView = null;
			
			WikitudePlugin.handleResumeInCordovaWebView(cordova.getActivity().getWindow().getDecorView().findViewById(android.R.id.content));
			return true;
		}
		return false;
	}


	private static int clearCacheFolder( final File dir, final int numDays ) {

		int deletedFiles = 0;
		if ( dir != null && dir.isDirectory() ) {
			try {
				for ( File child : dir.listFiles() ) {
 
					//first delete subdirectories recursively
					if ( child.isDirectory() ) {
						deletedFiles += clearCacheFolder( child, numDays );
					}

					//then delete the files and subdirectories in this dir
					//only empty directories can be deleted, so subdirs have been done first
					if ( child.lastModified() < new Date().getTime() - numDays * DateUtils.DAY_IN_MILLIS ) {
						if ( child.delete() ) {
							deletedFiles++;
						}
					}
				}
			} catch ( Exception e ) {
				e.printStackTrace();
			}
		}
		return deletedFiles;
	}

	private int convertArFeatures(JSONArray jsonArray) {
		int featuresBitMap = 0;
		for (int i = 0; i < jsonArray.length(); i++) {
			String feature = "";
			try {
				feature = (String) jsonArray.get(0);
			} catch (JSONException e) {
			}
			if (feature.equalsIgnoreCase("2d_tracking")) {
				featuresBitMap = featuresBitMap | StartupConfiguration.Features.Tracking2D;
			} else if (feature.equalsIgnoreCase("geo")) {
				featuresBitMap = featuresBitMap | StartupConfiguration.Features.Geo;
			}
		}
		if (featuresBitMap == 0) {
			featuresBitMap = StartupConfiguration.Features.Tracking2D | StartupConfiguration.Features.Geo;
		}
		return featuresBitMap;
	}

	/**
	 * Architect-Configuration required for proper set-up
	 * @param apiKey
	 * @param features 
	 * @return
	 */
	protected StartupConfiguration getStartupConfiguration( final String apiKey, int features, JSONObject startupConfiguration ) {
		StartupConfiguration.CameraPosition cameraPosition = CameraPosition.DEFAULT;
		try {
			if (startupConfiguration != null) {
				if (startupConfiguration.getString("camera_position").compareToIgnoreCase("front") == 0) {
					cameraPosition = StartupConfiguration.CameraPosition.FRONT;
				} else if (startupConfiguration.getString("camera_position").compareToIgnoreCase("back") == 0) {
					cameraPosition = StartupConfiguration.CameraPosition.BACK;
				}
			}
		} catch (JSONException e) {
		}

		/* no special set-up required in default Wikitude-Plugin, further things required in advanced usage (e.g. Vuforia Image Recognition) */
		StartupConfiguration config = new StartupConfiguration( apiKey, features, cameraPosition);
		config.setOrigin( StartupConfiguration.ORIGIN_PHONEGAP );
		return config;
	}

	/**
	 * add architectView to current screen
	 * @param apiKey developers's api key to use (hides watermarking/intro-animation if it matches your package-name)
	 * @param filePath the url (starting with http:// for online use; starting with LOCAL_ASSETS_PATH_ROOT if oyu want to load assets within your app-assets folder)
	 * @param features Augmented Reality mode ()
	 * @throws IOException might be thrown from ARchitect-SDK
	 */
	private void addArchitectView( final String apiKey, String filePath, int features, JSONObject startupConfiguration) throws IOException {
		if ( this.architectView == null ) {
			
			WikitudePlugin.releaseFocusInCordovaWebView(cordova.getActivity().getWindow().getDecorView().findViewById(android.R.id.content));
	
			this.architectView = new ArchitectViewPhoneGap( this.cordova.getActivity() , new OnKeyUpDownListener() {
	
				@Override
				public boolean onKeyUp(int keyCode, KeyEvent event) {
					if (architectView!=null && keyCode == KeyEvent.KEYCODE_BACK) {
						if (WikitudePlugin.this.locationProvider != null) {
							WikitudePlugin.this.locationProvider.onPause();
						}
						removeArchitectView();
						return true;
					} else {
						return false;
					}
				}
	
				@Override
				public boolean onKeyDown(int keyCode, KeyEvent event) {
					return architectView!=null && keyCode == KeyEvent.KEYCODE_BACK;
				}
			});
			
			this.architectView.setFocusableInTouchMode(true);
			this.architectView.requestFocus();

			this.locationListener = new LocationListener() {
	
				@Override
				public void onStatusChanged( String provider, int status, Bundle extras ) {
				}
	
				@Override
				public void onProviderEnabled( String provider ) {
				}
	
				@Override
				public void onProviderDisabled( String provider ) {
				}
	
				@Override
				public void onLocationChanged( final Location location ) {
					if (location!=null && !WikitudePlugin.this.useCustomLocation) {
						WikitudePlugin.this.lastKnownLocaton = location;
					if ( WikitudePlugin.this.architectView != null ) {
						if ( location.hasAltitude() ) {
							WikitudePlugin.this.architectView.setLocation( location.getLatitude(), location.getLongitude(), location.getAltitude(), location.getAccuracy() );
						} else {
							WikitudePlugin.this.architectView.setLocation( location.getLatitude(), location.getLongitude(), location.getAccuracy() );
						}
					}
					}
				}
			};

			/* add content view and fake initial life-cycle */
			(this.cordova.getActivity()).addContentView( this.architectView, new ViewGroup.LayoutParams( LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT ) );
			(this.cordova.getActivity()).setVolumeControlStream( AudioManager.STREAM_MUSIC );
	
			/* fake life-cycle calls, because activity is already up and running */
			this.architectView.onCreate( getStartupConfiguration( apiKey, features, startupConfiguration ) );
			this.architectView.onPostCreate();
	
			/* register self as url listener to fwd these native calls to PhoneGap */
			this.architectView.registerUrlListener( WikitudePlugin.this );
	
			/* load asset from local directory if prefix is used */
			if ( filePath.startsWith( WikitudePlugin.LOCAL_ASSETS_PATH_ROOT ) ) {
				filePath = filePath.substring( WikitudePlugin.LOCAL_ASSETS_PATH_ROOT.length() );
			}
			this.architectView.load( filePath );
	
			/* also a fake-life-cycle call (the last one before it is really shown in UI */
			this.architectView.onResume();
			if ((features & StartupConfiguration.Features.Geo) == features) {
				this.locationProvider = new LocationProvider( this.cordova.getActivity(), this.locationListener );
				this.locationProvider.onResume();
			}
		}
		
		// hide keyboard when adding AR view on top of views
		InputMethodManager inputManager = (InputMethodManager)            
				(this.cordova.getActivity()).getSystemService(Context.INPUT_METHOD_SERVICE); 
				    inputManager.hideSoftInputFromWindow((this.cordova.getActivity()).getCurrentFocus().getWindowToken(),      
				    InputMethodManager.HIDE_NOT_ALWAYS);
	}
	
	
	private static void releaseFocusInCordovaWebView(View rootView) {
		if (rootView instanceof CordovaWebView) { 
			((CordovaWebView)rootView).clearFocus();
		}
		else if (rootView instanceof ViewGroup) {
			final int childCount = ((ViewGroup)rootView).getChildCount();
			for (int i=0; i< childCount; i++) {
				WikitudePlugin.releaseFocusInCordovaWebView(((ViewGroup)rootView).getChildAt(i));
			}
		}		
	}

	/**
	 * To avoid JavaScript in Cordova staying paused after CordovaWebView lost focus call "handleResume" of the CordovaView in current Activity
	 * @param rootView the root view to search recursively for a CordovaWebView
	 */
	private static void handleResumeInCordovaWebView(final View rootView) {
		if (rootView instanceof CordovaWebView) { 
			((CordovaWebView)rootView).handleResume(true, true);
			((CordovaWebView)rootView).clearFocus();
			((CordovaWebView)rootView).requestFocus();
		}
		else if (rootView instanceof ViewGroup) {
			final int childCount = ((ViewGroup)rootView).getChildCount();
			for (int i=0; i< childCount; i++) {
				WikitudePlugin.handleResumeInCordovaWebView(((ViewGroup)rootView).getChildAt(i));
			}
		}
	}
	
	
	protected static class ArchitectViewPhoneGap extends ArchitectView{
		public static interface OnKeyUpDownListener {
			public boolean onKeyDown(int keyCode, KeyEvent event);
			
			public boolean onKeyUp(int keyCode, KeyEvent event);
		}
		
		private final OnKeyUpDownListener onKeyUpDownListener;
		
		@Deprecated
		public ArchitectViewPhoneGap(Context context) {
			super(context);
			this.onKeyUpDownListener = null;
		}
		
		public ArchitectViewPhoneGap(Context context, OnKeyUpDownListener onKeyUpDownListener) {
			super(context);
			this.onKeyUpDownListener = onKeyUpDownListener;
		}

		@Override
	    public boolean onKeyDown(int keyCode, KeyEvent event) {
			// forward onKeyDown events to listener
			return this.onKeyUpDownListener!=null &&  this.onKeyUpDownListener.onKeyDown(keyCode, event);
	    }
		
		@Override
		public boolean onKeyUp(int keyCode, KeyEvent event) {
			// forward onKeyUp events to listener
			return this.onKeyUpDownListener!=null &&  this.onKeyUpDownListener.onKeyUp(keyCode, event);
		}
		
		@Override
		protected void onFocusChanged(boolean gainFocus, int direction,
				Rect previouslyFocusedRect) {
			super.onFocusChanged(gainFocus, direction, previouslyFocusedRect);
			
			// ensure architectView does not loose focus on screen orientation changes etc.
			if (!gainFocus) {
				this.requestFocus();
			}
		}
	}
	
	/**
	 * Sample implementation of a locationProvider, feel free to polish this very basic approach (compare http://goo.gl/pvkXV )
	 * @author Wikitude GmbH
	 *
	 */
	private static class LocationProvider implements ILocationProvider {

		/** location listener called on each location update */
		private final LocationListener	locationListener;

		/** system's locationManager allowing access to GPS / Network position */
		private final LocationManager	locationManager;

		/** location updates should fire approximately every second */
		private static final int		LOCATION_UPDATE_MIN_TIME_GPS	= 1000;

		/** location updates should fire, even if last signal is same than current one (0m distance to last location is OK) */
		private static final int		LOCATION_UPDATE_DISTANCE_GPS	= 0;

		/** location updates should fire approximately every second */
		private static final int		LOCATION_UPDATE_MIN_TIME_NW		= 1000;

		/** location updates should fire, even if last signal is same than current one (0m distance to last location is OK) */
		private static final int		LOCATION_UPDATE_DISTANCE_NW		= 0;

		/** to faster access location, even use 10 minute old locations on start-up */
		private static final int		LOCATION_OUTDATED_WHEN_OLDER_MS	= 1000 * 60 * 10;

		/** is gpsProvider and networkProvider enabled in system settings */
		private boolean					gpsProviderEnabled, networkProviderEnabled;

		/** the context in which we're running */
		private final Context			context;


		public LocationProvider( final Context context, LocationListener locationListener ) {
			super();
			this.locationManager = (LocationManager)context.getSystemService( Context.LOCATION_SERVICE );
			this.locationListener = locationListener;
			this.context = context;
			this.gpsProviderEnabled = this.locationManager.isProviderEnabled( LocationManager.GPS_PROVIDER );
			this.networkProviderEnabled = this.locationManager.isProviderEnabled( LocationManager.NETWORK_PROVIDER );
		}

		@Override
		public void onPause() {
			if ( this.locationListener != null && this.locationManager != null && (this.gpsProviderEnabled || this.networkProviderEnabled) ) {
				this.locationManager.removeUpdates( this.locationListener );
			}
		}

		@Override
		public void onResume() {
			if ( this.locationManager != null && this.locationListener != null ) {

				// check which providers are available are available
				this.gpsProviderEnabled = this.locationManager.isProviderEnabled( LocationManager.GPS_PROVIDER );
				this.networkProviderEnabled = this.locationManager.isProviderEnabled( LocationManager.NETWORK_PROVIDER );

				/** is GPS provider enabled? */
				if ( this.gpsProviderEnabled ) {
					final Location lastKnownGPSLocation = this.locationManager.getLastKnownLocation( LocationManager.GPS_PROVIDER );
					if ( lastKnownGPSLocation != null && lastKnownGPSLocation.getTime() > System.currentTimeMillis() - LOCATION_OUTDATED_WHEN_OLDER_MS ) {
						locationListener.onLocationChanged( lastKnownGPSLocation );
					}
					this.locationManager.requestLocationUpdates( LocationManager.GPS_PROVIDER, LOCATION_UPDATE_MIN_TIME_GPS, LOCATION_UPDATE_DISTANCE_GPS, this.locationListener );
				}

				/** is Network / WiFi positioning provider available? */
				if ( this.networkProviderEnabled ) {
					final Location lastKnownNWLocation = this.locationManager.getLastKnownLocation( LocationManager.NETWORK_PROVIDER );
					if ( lastKnownNWLocation != null && lastKnownNWLocation.getTime() > System.currentTimeMillis() - LOCATION_OUTDATED_WHEN_OLDER_MS ) {
						locationListener.onLocationChanged( lastKnownNWLocation );
					}
					this.locationManager.requestLocationUpdates( LocationManager.NETWORK_PROVIDER, LOCATION_UPDATE_MIN_TIME_NW, LOCATION_UPDATE_DISTANCE_NW, this.locationListener );
				}

				/** user didn't check a single positioning in the location settings, recommended: handle this event properly in your app, e.g. forward user directly to location-settings, new Intent( Settings.ACTION_LOCATION_SOURCE_SETTINGS ) */
				if ( !this.gpsProviderEnabled && !this.networkProviderEnabled ) {
					Toast.makeText( this.context, "Please enable GPS and Network positioning in your Settings ", Toast.LENGTH_LONG ).show();
				}
			}
		}
	}
	
	private interface ILocationProvider {

		/**
		 * Call when host-activity is resumed (usually within systems life-cycle method)
		 */
		public void onResume();

		/**
		 * Call when host-activity is paused (usually within systems life-cycle method)
		 */
		public void onPause();

	}
	
}
