package com.wikitude.phonegap;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Date;
import java.util.Scanner;

import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CordovaWebView;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;

import android.text.format.DateUtils;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.view.ViewManager;

import com.wikitude.architect.ArchitectUrlListener;
import com.wikitude.architect.ArchitectView;
import com.wikitude.architect.ArchitectView.ArchitectConfig;



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
	private ArchitectView		architectView;

	/**
	 * callback-Id of url-invocation method
	 */
	private CallbackContext		urlInvokeCallback			= null;

	/**
	 * callback-id of "open"-action method
	 */
	private CallbackContext		openCallback				= null;
	

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
			if ( ArchitectView.isDeviceSupported( this.cordova.getActivity() ) && hasNeonSupport() ) {
				callContext.success( action + ": this device is ARchitect-ready" );
			} else {
				callContext.error( action + action + ":Sorry, this device is NOT ARchitect-ready" );
			}
			return true;
		}



		/* life-cycle's RESUME */
		if ( WikitudePlugin.ACTION_ON_RESUME.equals( action ) ) {

			if ( this.architectView != null ) {
				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						WikitudePlugin.this.architectView.onResume();
						callContext.success( action + ": architectView is present" );
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
			PluginResult result = new PluginResult( PluginResult.Status.NO_RESULT, action + ": registered callback" );
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
				final String apiKey = args.getString( 0 );
				final String filePath = args.getString( 1 );

				this.cordova.getActivity().runOnUiThread( new Runnable() {

					@Override
					public void run() {
						try {
							WikitudePlugin.this.addArchitectView( apiKey, filePath );

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
	 * @param url the invoked url (e.g. "myprotocoll://foo")
	 * @return true if call was handled properly
	 */
	@Override
	public boolean urlWasInvoked( String url ) {

		/* call callback-method if set*/
		if ( this.urlInvokeCallback != null ) {
			try {
				/* pass called url as String to callback-method */
				PluginResult res = new PluginResult( PluginResult.Status.OK, url );
				res.setKeepCallback( true );
				urlInvokeCallback.sendPluginResult( res );
				return true;
			} catch ( Exception e ) {
				urlInvokeCallback.error( "invalid url invoked: " + url );
			}
			return true;
		}
		return false;
	}
	
	/**
	 * workaround required until SDK Version 3.1, upcoming version will fix this issue
	 */
	private void pluginLifecycleWorkaround() {
		try {
			Thread.sleep(500);
		} catch (InterruptedException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
	}

	/**
	 * hides/removes ARchitect-View completely
	 * @return true if successful, false otherwise
	 */
	private boolean removeArchitectView() {
		if ( this.architectView != null ) {

			pluginLifecycleWorkaround();
						
			/* fake life-cycle calls, because activity is already up and running */
			this.architectView.onPause();
			
			pluginLifecycleWorkaround();
			
			this.architectView.onDestroy();

			// clean-up used temp-directory
			try {
				WikitudePlugin.clearCacheFolder( new File( ArchitectView.getCacheDirectoryAbsoluteFilePath( this.cordova.getActivity() ) ), 0 );
			} catch ( Exception e ) {
				// had troubles in clearing files from cache
				e.printStackTrace();
			}

			this.architectView.setVisibility( View.INVISIBLE );
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


	/**
	 * Architect-Configuration required for proper set-up
	 * @param apiKey
	 * @return
	 */
	protected ArchitectConfig getArchitectConfig( final String apiKey ) {
		/* no special set-up required in default Wikitude-Plugin, further things required in advanced usage (e.g. Vuforia Image Recognition) */
		ArchitectConfig config = new ArchitectConfig( apiKey );
		config.setOrigin( ArchitectConfig.ORIGIN_PHONEGAP );
		return config;
	}

	/**
	 * add architectView to current screen
	 * @param apiKey developers's api key to use (hides watermarking/intro-animation if it matches your package-name)
	 * @param filePath the url (starting with http:// for online use; starting with LOCAL_ASSETS_PATH_ROOT if oyu want to load assets within your app-assets folder)
	 * @throws IOException might be thrown from ARchitect-SDK
	 */
	private void addArchitectView( final String apiKey, String filePath ) throws IOException {
		if ( this.architectView == null ) {

			this.architectView = new ArchitectView( this.cordova.getActivity() );

			/* add content view and fake initial life-cycle */
			(this.cordova.getActivity()).addContentView( this.architectView, new ViewGroup.LayoutParams( LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT ) );

			/* fake life-cycle calls, because activity is already up and running */
			this.architectView.onCreate( getArchitectConfig( apiKey ) );
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

		}
	}
	
	
	/**
	 * 
	 * @return true if device chip has neon-command support
	 */
	private boolean hasNeonSupport() {
		/* Read cpu info */

		FileInputStream fis;
		try {
			fis = new FileInputStream("/proc/cpuinfo");

		} catch (FileNotFoundException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
			return false;
		}

		Scanner scanner = new Scanner(fis);

		boolean neonSupport = false;

		try {

			while (scanner.hasNextLine()) {

				if (!neonSupport && (scanner.findInLine("neon") != null)) {

					neonSupport = true;

				}

				scanner.nextLine();

			}

		} catch (Exception e) {

			Log.i("Wikitudeplugin",
					"error while getting info about neon support"
							+ e.getMessage());
			e.printStackTrace();

		} finally {

			scanner.close();

		}

		return neonSupport;
	}
	
	
	/**
	 * To avoid JavaScript in Cordova staying paused after CordovaWebView lost focus call "handleResume" of the CordovaView in current Activity
	 * @param rootView the root view to search recursively for a CordovaWebView
	 */
	private static void handleResumeInCordovaWebView(final View rootView) {
		if (rootView instanceof CordovaWebView) { 
			((CordovaWebView)rootView).handleResume(true, true);
		}
		else if (rootView instanceof ViewGroup) {
			final int childCount = ((ViewGroup)rootView).getChildCount();
			for (int i=0; i< childCount; i++) {
				WikitudePlugin.handleResumeInCordovaWebView(((ViewGroup)rootView).getChildAt(i));
			}
		}
	}
	
}
