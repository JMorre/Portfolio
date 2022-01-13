import numpy as np
import pandas as pd
import datetime

DEFECT_TAGS = ['C_Defect[126].History.Defects.ACC', 'C_Defect[127].History.Defects.ACC',
               'C_Defect[128].History.Defects.ACC', 'C_Defect[129].History.Defects.ACC',
               'C_Defect[20].History.Defects.ACC', 'C_Defect[327].History.Defects.ACC',
               'C_Defect[352].History.Defects.ACC', 'C_Defect[353].History.Defects.ACC',
               'C_Defect[354].History.Defects.ACC', 'C_Defect[355].History.Defects.ACC',
               'C_Defect[356].History.Defects.ACC', 'C_Defect[357].History.Defects.ACC',
               'C_Defect[358].History.Defects.ACC', 'C_Defect[359].History.Defects.ACC',
               'C_Defect[360].History.Defects.ACC', 'C_Defect[361].History.Defects.ACC',
               'C_Defect[41].History.Defects.ACC', 'C_Defect[42].History.Defects.ACC']

# Dictionary for tags to descriptions
TAG_DESC = {"C_R09_AxisEncoderTemps[16]": "FEA Backsheet S-Wrap Omega Axis EncoderTemp Actual",
            "C_R09_AxisEncoderTemps[22]": "LZ Backsheet Infeed Pull Roll Omega Axis EncoderTemp Actual",
            "CPX_Device_LZ_Controller[2].ActualPressure": "LZ Bonding Roll System Bond Load Pressure Actual",
            "CPX_Device_LZ_Controller[27].ActualPressure": "LZ Backsheet Airbar Control Pressure Actual",
            "Servo_S09_SERCOS_N16_F02_Ax05.ActualVelocity": "FEA Backsheet S-Wrap Omega Axis Velocity Actual",
            "Servo_S09_SERCOS_N16_F02_Ax05.PositionError": "FEA Backsheet S-Wrap Omega Axis PositionError Actual",
            "Servo_S09_SERCOS_N16_F02_Ax05.TorqueFeedback": "FEA Backsheet S-Wrap Omega Axis Torque Actual",
            "Servo_S09_SERCOS_N22_F03_Ax01.ActualVelocity": "LZ Backsheet Infeed Pull Roll Omega Axis Velocity Actual",
            "Servo_S09_SERCOS_N22_F03_Ax01.PositionError": "LZ Backsheet Infeed Pull Roll Omega Axis PositionError Actual",
            "Servo_S09_SERCOS_N22_F03_Ax01.TorqueFeedback": "LZ Backsheet Infeed Pull Roll Omega Axis Torque Actual",
            "C_Dancer_00.Status.ProportionalValveRef": "BLU Dws Process Prop Valve Dancer Control Pressure SP",
            "C_Dancer_01.Status.ProportionalValveRef": "BLU Ups Process Prop Valve Dancer Control Pressure SP",
            "C_Data_CS_B_Virtual_To_BLU.BLURegPhaseErr_mm": "f_BLU.BLU.Registration.Error.Position.Actual",
            "C_Data_PS_E_Zone6ToMain.Stops.StopCode[0]": "Z6 Stop Code",
            "C_Data_PS_E_Zone6ToMain.CautionBit": "Z6 Caution Code",
            "C_Splicebox_00.Status.RollACurrentDiameter": "BLU Splicebox_00 Status Roll A Current Diameter",
            "C_Splicebox_00.Status.RollBCurrentDiameter": "BLU Splicebox_00 Status Roll B Current Diameter",
            "C_Splicebox_01.Status.RollACurrentDiameter": "BLU Splicebox_01 Status Roll A Current Diameter",
            "C_Splicebox_01.Status.RollBCurrentDiameter": "BLU Splicebox_01 Status Roll B Current Diameter",
            "CPX_Device_BLU_Controller[0].ActualPressure": "BLU Dws Main Air Supply Pressure Actual",
            "CPX_Device_BLU_Controller[1].ActualPressure": "BLU Dws Splice Supply Pressure Actual",
            "CPX_Device_BLU_Controller[4].ActualPressure": "BLU Dws Dancer Control Position Actual",
            "CPX_Device_BLU_Controller[8].ActualPressure": "BLU Dws Splice Cut Pressure Actual",
            "CPX_Device_BLU_Controller[9].ActualPressure": "BLU Dws Splice Clamp Pressure Actual",
            "CPX_Device_BLU_Controller[13].ActualPressure": "BLU Ups Main Air Supply Pressure Actual",
            "CPX_Device_BLU_Controller[14].ActualPressure": "BLU Ups Splice Supply Pressure Actual",
            "CPX_Device_BLU_Controller[17].ActualPressure": "BLU Ups Dancer Control Position Actual",
            "CPX_Device_BLU_Controller[21].PressureSpt": "BLU Ups Splice Cut Pressure SP",
            "CPX_Device_BLU_Controller[22].PressureSpt": "BLU Ups Splice Clamp Pressure SP",
            "CPX_Device_BLU_Controller[23].ActualPressure": "BLU Ups Dancer Control Pressure Actual",
            "Servo_S13_SERCOS_N10_F00_Ax00.ActualVelocity": "BLU Dws A Unwind Spindle Axis Velocity Actual",
            "Servo_S13_SERCOS_N10_F00_Ax00.PositionError": "BLU Dws A Unwind Spindle Axis PositionError Actual",
            "Servo_S13_SERCOS_N10_F00_Ax00.TorqueFeedback": "BLU Dws A Unwind Spindle Axis Torque Actual",
            "Servo_S13_SERCOS_N12_F00_Ax01.ActualVelocity": "BLU Dws B Unwind Spindle Axis Velocity Actual",
            "Servo_S13_SERCOS_N12_F00_Ax01.PositionError": "BLU Dws B Unwind Spindle Axis PositionError Actual",
            "Servo_S13_SERCOS_N12_F00_Ax01.TorqueFeedback": "BLU Dws B Unwind Spindle Axis Torque Actual",
            "Servo_S13_SERCOS_N14_F00_Ax02.ActualVelocity": "BLU Dws Meter Omega Axis Velocity Actual",
            "Servo_S13_SERCOS_N14_F00_Ax02.PositionError": "BLU Dws Meter Omega Axis PositionError Actual",
            "Servo_S13_SERCOS_N14_F00_Ax02.TorqueFeedback": "BLU Dws Meter Omega Axis Torque Actual",
            "Servo_S13_SERCOS_N15_F00_Ax03.ActualVelocity": "BLU Dws Upper Omega Axis Velocity Actual",
            "Servo_S13_SERCOS_N15_F00_Ax03.PositionError": "BLU Dws Upper Omega Axis PositionError Actual",
            "Servo_S13_SERCOS_N15_F00_Ax03.TorqueFeedback": "BLU Dws Upper Omega Axis Torque Actual",
            "Servo_S13_SERCOS_N16_F00_Ax04.ActualVelocity": "BLU Dws Lower Omega Axis Velocity Actual",
            "Servo_S13_SERCOS_N16_F00_Ax04.PositionError": "BLU Dws Lower Omega Axis PositionError Actual",
            "Servo_S13_SERCOS_N16_F00_Ax04.TorqueFeedback": "BLU Dws Lower Omega Axis Torque Actual",
            "Servo_S13_SERCOS_N20_F00_Ax05.ActualVelocity": "BLU Ups A Unwind Spindle Axis Velocity Actual",
            "Servo_S13_SERCOS_N20_F00_Ax05.PositionError": "BLU Ups A Unwind Spindle Axis PositionError Actual",
            "Servo_S13_SERCOS_N20_F00_Ax05.TorqueFeedback": "BLU Ups A Unwind Spindle Axis Torque Actual",
            "Servo_S13_SERCOS_N22_F00_Ax06.ActualVelocity": "BLU Ups B Unwind Spindle Axis Velocity Actual",
            "Servo_S13_SERCOS_N22_F00_Ax06.PositionError": "BLU Ups B Unwind Spindle Axis PositionError Actual",
            "Servo_S13_SERCOS_N22_F00_Ax06.TorqueFeedback": "BLU Ups B Unwind Spindle Axis Torque Actual",
            "Servo_S13_SERCOS_N24_F00_Ax07.ActualVelocity": "BLU Ups Meter Omega Axis Velocity Actual",
            "Servo_S13_SERCOS_N24_F00_Ax07.PositionError": "BLU Ups Meter Omega Axis PositionError Actual",
            "Servo_S13_SERCOS_N24_F00_Ax07.TorqueFeedback": "BLU Ups Meter Omega Axis Torque Actual",
            "Servo_S13_SERCOS_N25_F00_Ax08.ActualVelocity": "BLU Pitch Control Omega Axis Velocity Actual",
            "Servo_S13_SERCOS_N25_F00_Ax08.PositionError": "BLU Pitch Control Omega Axis PositionError Actual",
            "Servo_S13_SERCOS_N25_F00_Ax08.TorqueFeedback": "BLU Pitch Control Omega Axis Torque Actual",
            "C_Data_PS_MainPLC_CommonData.Size": "Current Product Size",
            "C_LineMode": "Global MODE Enum Tag Bit 0",
            "C_LineState": "Global STATE Enum Tag Bit 0",
            "C_PhasingInfo[169]": "PhaseAdjust BLU_Pitch",
            "C_CurrentStopList[0]": "MAIN Stop Code",
            "Virtual_LineReference_P.CommandVelocity": "Virtual Line Speed",
            "C_Defect[20].History.Defects.ACC": "R020 BLU REGISTRATION",
            "C_Defect[41].History.Defects.ACC": "R041 BLU UPSTREAM SPLICE FAILSAFE",
            "C_Defect[42].History.Defects.ACC": "R042 BLU DOWNSTRM SPLICE FAILSAFE",
            "C_Defect[126].History.Defects.ACC": "R126 LZ UPSTREAM BLU M/T DS",
            "C_Defect[127].History.Defects.ACC": "R127 LZ UPSTREAM BLU M/T OP",
            "C_Defect[128].History.Defects.ACC": "R128 LZ DOWNSTREAM BLU M/T DS",
            "C_Defect[129].History.Defects.ACC": "R129 LZ DOWNSTREAM BLU M/T OP",
            "C_Defect[327].History.Defects.ACC": "R327 VISCC2 BLU REGISTRATION",
            "C_Defect[352].History.Defects.ACC": "R352 VISLZ1 BLU SPLICE",
            "C_Defect[353].History.Defects.ACC": "R353 VISLZ1 BLU SPLICE LE",
            "C_Defect[354].History.Defects.ACC": "R354 VISLZ1 BLU U/S SPLICE",
            "C_Defect[355].History.Defects.ACC": "R355 VISLZ1 BLU U/S SPLICE LE",
            "C_Defect[356].History.Defects.ACC": "R356 VISLZ1 BLU D/S SPLICE",
            "C_Defect[357].History.Defects.ACC": "R357 VISLZ1 BLU D/S SPLICE LE",
            "C_Defect[358].History.Defects.ACC": "R358 VISLZ1 LZ SPLICE",
            "C_Defect[359].History.Defects.ACC": "R359 VISLZ1 LZ SPLICE LE",
            "C_Defect[360].History.Defects.ACC": "R360 VISLZ1 BLU M/T @LZ DS",
            "C_Defect[361].History.Defects.ACC": "R361 VISLZ1 BLU M/T @LZ OP",
            "C_SpliceFailSafe[8].History.CountedPads_NipDetector[4]": "Splice BLU_UP NipDetectorPads",
            "C_SpliceFailSafe[8].History.NipDetector_mm[4]": "Splice BLU_UP NipDetectorDistance",
            "C_SpliceFailSafe[9].History.CountedPads_NipDetector[4]": "Splice BLU_DN NipDetectorPads",
            "C_SpliceFailSafe[9].History.NipDetector_mm[4]": "Splice BLU_DN NipDetectorDistance",
            "Melter[8].PumpActualSpeed[2]": "300 P803 P02 BLU Lam Velocity Actual",
            "Melter[8].Pressure_A[2]": "300 P803 P02 BLU Lam S1 Pressure Actual",
            "C_BLU_Autophasing_AOI.Sts_Detection_Feedback_prod": "Backsheet autophasing indication",
            "VISCC2Autophase.BLUCenterPosDS": "BLU Autophase Center Position Drive",
            "VISCC2Autophase.BLUCenterPosOP": "BLU Autophase Center Position Op"}


# This function recieves a dataframe read from a DF csv file, and then determines
# all of the indexes where the tag 'Virtual_LineReference_P.CommandVelocity' is below a
# certain value.  That value is 19.9 by default (since the usual run speed is 20.0), but
# can be set to something else.
# TODO: there are still defects that occur sometimes just before and after the factory has
# started or stopped.  This function is taking out chunks of data where the factory is down,
# but we probably want it to also remove 5 seconds or so on either side of those chunks of
# time to account for these defects.  Find an efficient way to accomplish that
def remove_line_downtime(data, command_velocity_threshold = 19.9):
    return data.drop(data[data['Virtual_LineReference_P.CommandVelocity'] < command_velocity_threshold].index)


# This function recieves a dataframe with downtime removed, then determines at each point
# how many defects occurred since the last point.  So we have a sum of defect changes, which
# is returned as a single column pandas series (delta_defect_column, indicating it is the change
# in defects at each point)
def get_defect_columns(data):
    defects = data[DEFECT_TAGS]
    delta_defect_column = np.sum((defects - defects.shift()), axis = 1).astype(int)
    delta_defect_column = pd.Series(delta_defect_column, index = data.index)
    delta_defect_column.iloc[0] = 0
    return delta_defect_column

# This function recieves a dataframe OR defects column as returned by get_defect_columns.  If
# no defects column is included, it will run get_defects_column on the data to generate one.
# It then iterates through the defects column and determines where 'clusters' of defects are occurring.
# There are 3 other variables involved here that can be overridden:
# target_length: how much time (in seconds) directly before a defect cluster should be assigned the variable 1?
# cluster_tolerance: how much time (in seconds) can come between defects before they are considered part of different clusters?
# cluster_threshold: how many defects need to be included in a cluster for it to be considered a cluster?
# TODO: this implementation could potentially be more efficient.  I don't yet know how to vectorize it or take advantage
# of other pandas functions to speed up processing, but it has potential to be faster.
# also, after line downtime is removed, this function could potentially make the output variable span across gaps, which
# is not how it should be.  Accounting for this could help improve accuracy.
def define_target(data = None, defects = None, target_length = 30, cluster_tolerance = 5, cluster_threshold = 5):
    if defects is None: # if no delta defect column is provided: create it
        defects = get_defect_columns(data)
    defects.index = pd.to_datetime(defects.index) # convert the index to datetime objects

    # initialize variables
    dcount = 0
    scount = 0
    start = defects.index[0]
    prev = defects.index[0]
    iprev = defects.index[0]
    clusters = []

    # iterate over every time-value pair in the delta defect column
    for index, val in defects.items():
        # if the value indicates a defect occurred:
        if val > 0:
            if dcount == 0: start = index # if this is the first defect in the current prospective cluster, set "start" to this time
            dcount += val # add the value to the current prospective cluster's defect counter
            prev = index # set "prev", indicating that this is the current endpoint of the prospective cluster
            scount = 0 # reset the consecutive non-defect counter

        # if the defect counter is nonzero, then there is currently a prospective cluster to consider:
        if dcount > 0:
            scount += 1 # increment the consecutive non-defect counter

            # if end of object, or the non-defect counter exceeds the cluster_tolerance variable, then we need to package or reject this prospective cluster
            if scount > cluster_tolerance or index == defects.index[-1]:
                # if there are enough defects included in this cluster to package it, then we do so
                if dcount > cluster_threshold:
                    clusters.append((start, prev, dcount))
                # reset the defect counter, indicating that we've finished processing the prospective cluster
                dcount = 0

    # initialize other variables
    defects[:] = 0
    target_time = datetime.timedelta(seconds = target_length) # a timedelta object corresponding to our desired target variable length
    one_sec = datetime.timedelta(seconds = 1)

    # iterate over each defined cluster
    for cluster in clusters:
        start = cluster[0] - target_time # define the start time of our target (output) variable's 1's
        if start < defects.index[0]: start = defects.index[0] # default to first value if out of bounds
        while not start in defects.index: start += one_sec # if the "start" point is part of the ommitted downtime, then find the nearest up-time instead
        defects[start:cluster[0]] = 1 # everywhere from "start" as calculated to just before the start point of the cluster is set to 1

    # return the new binary target variable, corresponding to 30 (default) second "critical moments" before defects are created in clusters
    return defects
