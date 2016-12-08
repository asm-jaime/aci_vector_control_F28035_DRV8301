/* =================================================================================
File name:        F2803XQEP.H                     
Target   :             F2803x family
===================================================================================*/

#ifndef __RESOLVER_H__
#define __RESOLVER_H__

/*-----------------------------------------------------------------------------
Define the structure of the RESOLVER Driver Object
-----------------------------------------------------------------------------*/
typedef struct {
                    _iq ElecTheta;       // Output: Motor Electrical angle (Q24)
                    _iq MechTheta;       // Output: Motor Mechanical Angle (Q24)
                    _iq RawTheta;        // Variable: Raw position data from resolver (Q0)
                    _iq Speed;           // Variable: Speed data from resolver (Q4)
                    _iq InitTheta;       // Parameter: Raw angular offset between encoder index and phase a (Q0)
                    _iq MechScaler;      // Parameter: 0.9999/total count (Q30)
                    _iq StepsPerTurn;    // Parameter: Number of discrete positions (Q0)
                 Uint16 PolePairs;       // Parameter: Number of pole pairs (Q0)

                }  RESOLVER;

/*-----------------------------------------------------------------------------
Define a RESOLVER_handle
-----------------------------------------------------------------------------*/
//typedef RESOLVER *RESOLVER_handle;

/*-----------------------------------------------------------------------------
Default initializer for the QEP Object.
-----------------------------------------------------------------------------*/
#define RESOLVER_DEFAULTS {                                                   \
                               0x0,            /*  ElecTheta    - (Q24)  */   \
                               0x0,            /*  MechTheta    - (Q24)  */   \
                               0x0,            /*  RawTheta     - (Q0)   */   \
                               0x0,            /*  Speed        - (Q4)   */   \
                               0x0,            /*  InitTheta    - (Q0)   */   \
                               0x00020000,     /*  MechScaler   - (Q30)  */   \
                               0x0,            /*  StepsPerTurn - (Q0)   */   \
                               2,              /*  PolePairs    - (Q0)   */   \
       }

// **************************************************************************************
/*-----------------------------------------------------------------------------
       Resolver Interface Update Macro Definitions
-----------------------------------------------------------------------------*/

#define  RESOLVER_MACRO(v)                                                                      \
                                                                                                \
/* Compute the mechanical angle in Q24 */                                                       \
    v.MechTheta   = v.RawTheta - v.InitTheta;      /* MechTheta in step counts */               \
    v.MechTheta   = __qmpy32by16(v.MechScaler,(int16)v.MechTheta,31);  /* Q15 = Q30*Q0 */       \
    v.MechTheta  &= 0x7FFF;                        /* Wrap around 0x07FFF*/                     \
    v.MechTheta <<= 9;                             /* Q15 -> Q24 */                             \
                                                                                                \
/* Compute the electrical angle in Q24 */                                                       \
    v.ElecTheta  = v.PolePairs * v.MechTheta;      /* Q24 = Q0*Q24 */                           \
    v.ElecTheta &= 0x00FFFFFF;                     /* Wrap around 0x00FFFFFF */


#define  RESOLVER_MACRO_F(v)                                                                    \
                                                                                                \
/* Compute the mechanical angle in Q24 */                                                       \
    v.MechTheta   = v.RawTheta - v.InitTheta;      /* MechTheta in step counts */               \
    v.MechTheta   = (v.MechScaler*v.MechTheta);  /* Q15 = Q30*Q0 */                             \
    if(v.MechTheta>1.0) v.MechTheta=v.MechTheta-1.0;                                            \
/* Compute the electrical angle in Q24 */                                                       \
    v.ElecTheta  = _IQfrac(v.PolePairs * v.MechTheta);      /* Q24 = Q0*Q24 */

#endif // __RESOLVER_H__
