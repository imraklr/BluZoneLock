package imraklr.bluzonelock.domain.service

import android.bluetooth.BluetoothSocket
import android.os.Bundle
import android.os.Handler
import java.io.IOException
import java.io.InputStream
import java.io.OutputStream

private const val MESSAGE_READ: Int = 0
private const val MESSAGE_WRITE: Int = 1
private const val MESSAGE_TOAST: Int = 2
private const val BUFFER_SIZE: Int = 1024

/**
 * Service class for managing Bluetooth connections and data transfer.
 *
 * @property handler Handler for receiving messages from Bluetooth service.
 *
 * @author <a href="https://github.com/imraklr">Rakesh Kumar</a>
 */
class BluetoothService(
    private val handler: Handler
) {

    /**
     * Thread class for managing a connected Bluetooth socket.
     *
     * @property socket Bluetooth socket connected to the remote device.
     */
    inner class ConnectedThread(private val socket: BluetoothSocket) : Thread() {

        private val inStream: InputStream = socket.inputStream
        private val outStream: OutputStream = socket.outputStream
        private val buffer: ByteArray = ByteArray(BUFFER_SIZE) // Buffer for the stream

        /**
         * Runs the thread to listen for input data from the Bluetooth socket.
         */
        override fun run() {
            var numBytes: Int // Bytes returned from read()

            // Keep listening to the InputStream until an exception occurs.
            while (true) {
                // Read from the InputStream.
                numBytes = try {
                    inStream.read(buffer)
                } catch (e: IOException) {
                    break
                }

                // Send the obtained bytes to the UI activity.
                val readMsg = handler.obtainMessage(
                    MESSAGE_READ, numBytes, -1,
                    buffer
                )
                readMsg.sendToTarget()
            }
        }

        /**
         * Writes data to the output stream of the Bluetooth socket.
         *
         * @param bytes Data to be written to the remote device.
         */
        fun write(bytes: ByteArray) {
            try {
                outStream.write(bytes)
            } catch (e: IOException) {
                // Send a failure message back to the activity.
                val writeErrorMsg = handler.obtainMessage(MESSAGE_TOAST)
                val bundle = Bundle().apply {
                    putString("toast", "Couldn't send data to the other device")
                }
                writeErrorMsg.data = bundle
                handler.sendMessage(writeErrorMsg)
                return
            }

            // Share the sent message with the UI activity.
            val writtenMsg = handler.obtainMessage(
                MESSAGE_WRITE, -1, -1, buffer
            )
            writtenMsg.sendToTarget()
        }

        /**
         * Cancels the connection by closing the Bluetooth socket.
         */
        fun cancel() {
            try {
                socket.close()
            } catch (_: IOException) {}
        }
    }
}
