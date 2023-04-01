/*
 * KalmanFilter.h
 *
 *  Created on: May 15, 2022
 *      Author: fame
 */

#ifndef INC_LIBRARY_KALMANFILTER_H_
#define INC_LIBRARY_KALMANFILTER_H_

typedef struct {
	/* Parameter */
	double R;
	double Q;

	/* KF "memory" */
	double x1;
	double x2;
	double p11;
	double p12;
	double p21;
	double p22;
	double dt;
} KalmanFilter;

void KalmanFilter_Init(KalmanFilter *dev, double x1,double x2,double p11,double p12,double p21,double p22, double R, double Q, double dt);
void KalmanFilter_Update(KalmanFilter *dev,double theta_k);

#endif /* INC_LIBRARY_KALMANFILTER_H_ */
