cd ../Sources/HLS

cd SimpleGpio
./BuildSimpleGpio.sh &
cd ..

cd SignalGenerator
./BuildSignalGenerator.sh &
cd ..

cd Multiplier
./BuildMultiplier.sh &
cd ..

cd StreamControl
./BuildStreamControl.sh &
cd ..

cd ../..
cd Scripts

wait
