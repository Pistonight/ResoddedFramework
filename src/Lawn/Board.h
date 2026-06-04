#ifndef __BOARD_H__
#define __BOARD_H__

#include "../ConstEnums.h"
#include "../Sexy.TodLib/DataArray.h"
#include "../SexyAppFramework/Widget.h"
#include "../SexyAppFramework/ButtonListener.h"

#include "Plant.h"
#include "Zombie.h"
#include "Projectile.h"
#include "Coin.h"
#include "LawnMower.h"
#include "GridItem.h"

using namespace Sexy;

#define MAX_GRID_SIZE_X 9
#define MAX_GRID_SIZE_Y 6
#define MAX_ZOMBIES_IN_WAVE 50
#define MAX_ZOMBIE_WAVES 100
#define MAX_GRAVE_STONES MAX_GRID_SIZE_X *MAX_GRID_SIZE_Y
#define MAX_POOL_GRID_SIZE 10
#define MAX_RENDER_ITEMS 2048
#define PROGRESS_METER_COUNTER 150
#define MAX_PLANTS_SIZE 1024U
#define MAX_ZOMBIES_SIZE 1024U
#define MAX_PROJECTILE_SIZE 1024U
#define MAX_COIN_SIZE 1024U
#define MAX_LAWN_MOWER_SIZE 32U
#define MAX_GRID_ITEM_SIZE 128U

class LawnApp;
class CursorObject;
class CursorPreview;
class GameButton;
class MessageWidget;
class SeedBank;
class ToolTipWidget;
class CutScene;
class Challenge;
class Reanimation;
class DataSync;
class TodParticleSystem;
namespace Sexy
{
class Graphics;
class ButtonWidget;
class WidgetManager;
class Image;
class MTRand;
} // namespace Sexy

class HitResult
{
  public:
	void *mObject;
	GameObjectType mObjectType;
};

class RenderItem
{
  public:
	RenderObjectType mRenderObjectType;
	int mZPos;
	union {
		GameObject *mGameObject;
		Plant *mPlant;
		Zombie *mZombie;
		Coin *mCoin;
		Projectile *mProjectile;
		CursorPreview *mCursorPreview;
		TodParticleSystem *mParticleSytem;
		Reanimation *mReanimation;
		GridItem *mGridItem;
		LawnMower *mMower;
		BossPart mBossPart;
		int mBoardGridY;
	};
};
bool RenderItemSortFunc(const RenderItem &theItem1, const RenderItem &theItem2);

struct ZombiePicker
{
	int mZombieCount;
	int mZombiePoints;
	int mZombieTypeCount[NUM_ZOMBIE_TYPES];
	int mAllWavesZombieTypeCount[NUM_ZOMBIE_TYPES];
};

/*inline*/ void ZombiePickerInitForWave(ZombiePicker *theZombiePicker);
/*inline*/ void ZombiePickerInit(ZombiePicker *theZombiePicker);

struct PlantsOnLawn
{
	Plant *mUnderPlant;
	Plant *mPumpkinPlant;
	Plant *mFlyingPlant;
	Plant *mNormalPlant;
};

struct BungeeDropGrid
{
	TodWeightedGridArray mGridArray[MAX_GRID_SIZE_X * MAX_GRID_SIZE_Y];
	int mGridArrayCount;
};

class Board : public Widget, public ButtonListener
{
  public:
	LawnApp *mApp;													  //+0x8C
	DataArray<Zombie> mZombies;										  //+0x90
	DataArray<Plant> mPlants;										  //+0xAC
	DataArray<Projectile> mProjectiles;								  //+0xC8
	DataArray<Coin> mCoins;											  //+0xE4
	DataArray<LawnMower> mLawnMowers;								  //+0x100
	DataArray<GridItem> mGridItems;									  //+0x11C
	CursorObject *mCursorObject;									  //+0x138
	CursorPreview *mCursorPreview;									  //+0x13C
	MessageWidget *mAdvice;											  //+0x140
	SeedBank *mSeedBank;											  //+0x144
	GameButton *mMenuButton;										  //+0x148
	GameButton *mStoreButton;										  //+0x14C
	bool mIgnoreMouseUp;											  //+0x150
	ToolTipWidget *mToolTip;										  //+0x154
	Font *mDebugFont;												  //+0x158
	CutScene *mCutScene;											  //+0x15C
	Challenge *mChallenge;											  //+0x160

#if LAWN_DEBUG_TOOLS
	Zombie *mDebugSelectedZombie;
	Plant  *mDebugSelectedPlant;
#endif

	bool mPaused;													  //+0x164
	GridSquareType mGridSquareType[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y]; //+0x168
	int mGridCelLook[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y];				  //+0x240
	int mGridCelOffset[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y][2];		  //+0x318
	int mGridCelFog[MAX_GRID_SIZE_X][MAX_GRID_SIZE_Y + 1];			  //+0x4C8
	bool mEnableGraveStones;										  //+0x5C4
	int mSpecialGraveStoneX;										  //+0x5C8
	int mSpecialGraveStoneY;										  //+0x5CC
	float mFogOffset;												  //+0x5D0
	int mFogBlownCountDown;											  //+0x5D4
	PlantRowType mPlantRow[MAX_GRID_SIZE_Y];						  //+0x5D8
	int mWaveRowGotLawnMowered[MAX_GRID_SIZE_Y];					  //+0x5F0
	int mBonusLawnMowersRemaining;									  //+0x608
	int mIceMinX[MAX_GRID_SIZE_Y];									  //+0x60C
	int mIceTimer[MAX_GRID_SIZE_Y];									  //+0x624
	ParticleSystemID mIceParticleID[MAX_GRID_SIZE_Y];				  //+0x63C
	TodSmoothArray mRowPickingArray[MAX_GRID_SIZE_Y];				  //+0x654
	ZombieType mZombiesInWave[MAX_ZOMBIE_WAVES][MAX_ZOMBIES_IN_WAVE]; //+0x6B4
	bool mZombieAllowed[100];										  //+0x54D4
	int mSunCountDown;												  //+0x5538
	int mNumSunsFallen;												  //+0x553C
	int mShakeCounter;												  //+0x5540
	int mShakeAmountX;												  //+0x5544
	int mShakeAmountY;												  //+0x5548
	BackgroundType mBackground;										  //+0x554C
	int mLevel;														  //+0x5550
	int mSodPosition;												  //+0x5554
	int mPrevMouseX;												  //+0x5558
	int mPrevMouseY;												  //+0x555C
	int mSunMoney;													  //+0x5560
	int mNumWaves;													  //+0x5564
	int mMainCounter;												  //+0x5568
	int mEffectCounter;												  //+0x556C
	int mDrawCount;													  //+0x5570
	int mRiseFromGraveCounter;										  //+0x5574
	int mOutOfMoneyCounter;											  //+0x5578
	int mCurrentWave;												  //+0x557C
	int mTotalSpawnedWaves;											  //+0x5580
	TutorialState mTutorialState;									  //+0x5584
	ParticleSystemID mTutorialParticleID;							  //+0x5588
	int mTutorialTimer;												  //+0x558C
	int mLastBungeeWave;											  //+0x5590
	int mZombieHealthToNextWave;									  //+0x5594
	int mZombieHealthWaveStart;										  //+0x5598
	int mZombieCountDown;											  //+0x559C
	int mZombieCountDownStart;										  //+0x55A0
	int mHugeWaveCountDown;											  //+0x55A4
	bool mHelpDisplayed[NUM_ADVICE_TYPES];							  //+0x55A8
	AdviceType mHelpIndex;											  //+0x55EC
	bool mFinalBossKilled;											  //+0x55F0
	bool mShowShovel;												  //+0x55F1
	int mCoinBankFadeCount;											  //+0x55F4
	DebugTextMode mDebugTextMode;									  //+0x55F8
	bool mLevelComplete;											  //+0x55FC
	int mBoardFadeOutCounter;										  //+0x5600
	int mNextSurvivalStageCounter;									  //+0x5604
	int mScoreNextMowerCounter;										  //+0x5608
	bool mLevelAwardSpawned;										  //+0x560C
	int mProgressMeterWidth;										  //+0x5610
	int mFlagRaiseCounter;											  //+0x5614
	int mIceTrapCounter;											  //+0x5618
	int mBoardRandSeed;												  //+0x561C
	ParticleSystemID mPoolSparklyParticleID;						  //+0x5620
	ReanimationID mFwooshID[MAX_GRID_SIZE_Y][12];					  //+0x5624
	int mFwooshCountDown;											  //+0x5744
	int mTimeStopCounter;											  //+0x5748
	bool mDroppedFirstCoin;											  //+0x574C
	int mFinalWaveSoundCounter;										  //+0x5750
	int mCobCannonCursorDelayCounter;								  //+0x5754
	int mCobCannonMouseX;											  //+0x5758
	int mCobCannonMouseY;											  //+0x575C
	bool mKilledYeti;												  //+0x5760
	bool mMustacheMode;												  //+0x5761
	bool mSuperMowerMode;											  //+0x5762
	bool mFutureMode;												  //+0x5763
	bool mPinataMode;												  //+0x5764
	bool mDanceMode;												  //+0x5765
	bool mDaisyMode;												  //+0x5766
	bool mSukhbirMode;												  //+0x5767
	BoardResult mPrevBoardResult;									  //+0x5768
	int mTriggeredLawnMowers;										  //+0x576C
	int mPlayTimeActiveLevel;										  //+0x5770
	int mPlayTimeInactiveLevel;										  //+0x5774
	int mMaxSunPlants;												  //+0x5778
	uint32_t mStartDrawTime;										  //+0x577C
	uint32_t mIntervalDrawTime;										  //+0x5780
	int mIntervalDrawCountStart;									  //+0x5784
	float mMinFPS;													  //+0x5788
	int mPreloadTime;												  //+0x578C
	int mGameID;													  //+0x5790
	int mGravesCleared;
	int mPlantsEaten;
	int mPlantsShoveled;
	int mPlantsPlaced;
	int mCoinsCollected;
	int mDiamondsCollected;
	int mPottedPlantsCollected;
	int mChocolateCollected;
	int mPennyPincherStreak;
	bool mDontPeaUsedPeashooter;
	bool mGroundedUsedCatapult;
	bool mGoodMorningUsedNonFungus;
	bool mNoFungusUsedFungus;
	int mGargantuarsKillsByCornCob;

#if SEXY_USE_CONTROLLER
	float mGamepadX;
	float mGamepadY;
	float mVisualGamepadX;
	float mVisualGamepadY;
	bool mGamepadIgnoreChallenge;
	// Previous button states, used to detect press-once vs hold
	bool mGamepadPrevSouth;     // A
	bool mGamepadPrevEast;      // B
	bool mGamepadPrevWest;      // X
	bool mGamepadPrevNorth;     // Y
	bool mGamepadPrevStart;     // Start
	bool mGamepadPrevLShoulder; // LB
	bool mGamepadPrevRShoulder; // RB
	bool mGamepadPrevLTrigger;  // LT
	bool mGamepadPrevRTrigger;  // RT
	// D-Pad accumulators for cell-to-cell stepping (one step per press)
	float mGamepadDpadXAccum;
	float mGamepadDpadYAccum;
#endif

  public:
	Board(LawnApp *theApp);
	virtual ~Board();

	/// @brief Dispose of the Board objects manually
	void DisposeBoard();
	/// @return Total value of the Sun that is being collected
	int CountSunBeingCollected();
	/// @brief Draw all GameObjects to the Board
	/// @param g Graphics object
	void DrawGameObjects(Graphics *g);
	/// @brief Clear the cursor of any object
	void ClearCursor();
	/*inline*/ bool AreEnemyZombiesOnScreen();
	LawnMower *FindLawnMowerInRow(int theRow);
	inline bool SyncState(DataSync &theDataSync)
	{ /* 未发现 */
		return true;
	}
	/*inline*/ void SaveGame(const std::string &theFileName);
	/// @brief Load the game state from the save file
	/// @return True if it loaded successfully
	bool LoadGame(const std::string &theFileName);
	void InitLevel();
	/// @brief Display an advice if it wasn't displayed before
	void DisplayAdvice(const SexyString &theAdvice, MessageStyle theMessageStyle, AdviceType theHelpIndex);
	/// @brief Start the level
	void StartLevel();
	Plant *AddPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
	Projectile *AddProjectile(int theX, int theY, int theRenderOrder, int theRow, ProjectileType theProjectileType);
	Coin *AddCoin(int theX, int theY, CoinType theCoinType, CoinMotion theCoinMotion);
	/// @brief Remove the SeedPacket from the Cursor
	void RefreshSeedPacketFromCursor();
	/// @return Get the ZombieType that will rise of the grave if we have theZombiePoints available
	ZombieType PickGraveRisingZombieType(int theZombiePoints);
	/// @return Get the ZombieType based on theWaveIndex and available theZombiePoints
	ZombieType PickZombieType(int theZombiePoints, int theWaveIndex, ZombiePicker *theZombiePicker);
	/// @return	Row Index for theZombieType
	int PickRowForNewZombie(ZombieType theZombieType);
	/*inline*/ Zombie *AddZombie(ZombieType theZombieType, int theFromWave);
	/// @brief Spawn a wave of Zombies
	void SpawnZombieWave();
	/// @brief Remove all zombies from the Board
	void RemoveAllZombies();
	/// @brief Remove all zombies that are bound to cutscenes
	void RemoveCutsceneZombies();
	/// @brief Spawn all final-flag Zombies from the GraveStones
	void SpawnZombiesFromGraves();
	/// @brief Determines if a plant can be placed.
	/// @param theGridX The Grid X Coordinate
	/// @param theGridY The Grid Y Coordinate
	/// @param theSeedType The SeedType to check
	/// @return Reason for planting here (inspect PlantingReason enum)
	PlantingReason CanPlantAt(int theGridX, int theGridY, SeedType theSeedType);
	/// @brief On Mouse Movement
	virtual void MouseMove(int x, int y);
	/// @brief On Mouse Drag
	virtual void MouseDrag(int x, int y);
	/// @brief Handle a mouse down press
	virtual void MouseDown(int x, int y, int theClickCount);
	/// @brief Handle a mouse up de-press
	virtual void MouseUp(int x, int y, int theClickCount);
	/// @brief Process a keyboard character press
	/// @param theChar SexyChar that was pressed (UTF-8 friendly)
	virtual void KeyChar(SexyChar theChar);
	virtual void KeyUp(KeyCode theKey)
	{
		;
	}
	/// @brief Process a KeyCode press
	/// @param theKey KeyCode that has been pressed
	virtual void KeyDown(KeyCode theKey);
	/// @brief Update the widget
	virtual void Update();
	/// @brief Update the Widgets currently active (MarkDirty + BringToFront)
	void UpdateLayers();
	/// @brief Draw the Widget
	/// @param g Graphics object
	virtual void Draw(Graphics *g);
	/// @brief Draw the lawn
	/// @param g Graphics object
	void DrawBackdrop(Graphics *g);
	virtual void ButtonMouseEnter(int theId)
	{
		;
	}
	virtual void ButtonMouseLeave(int theId)
	{
		;
	}
	virtual void ButtonPress(int theId)
	{
		;
	}
	/*inline*/ void AddSunMoney(int theAmount);
	/// @return True if there is enough Sun, False if we can't afford it
	bool TakeSunMoney(int theAmount);
	/*inline*/ bool CanTakeSunMoney(int theAmount);
	/*inline*/ void Pause(bool thePause);
	inline bool MakeEasyZombieType()
	{ /* 未发现 */
		return false;
	}
	/// @brief Try to save the current state to the profile's save folder
	void TryToSaveGame();
	/*inline*/ bool NeedSaveGame();
	/*inline*/ bool RowCanHaveZombies(int theRow);
	/// @brief Delete all arrays that the board has
	void ProcessDeleteQueue();
	/// @return True if the player chooses the SeedPackets
	bool ChooseSeedsOnCurrentLevel();
	/// @return The max number of plants in the SeedBank
	int GetNumSeedsInBank();
	/*inline*/ bool StageIsNight();
	/*inline*/ bool StageHasPool();
	/*inline*/ bool StageHas6Rows();
	/*inline*/ bool StageHasFog();
	/// @return True if the Stage has GraveStones
	bool StageHasGraveStones();

	/// @return The translated Grid X
	/// @param theX The X Coordinate in World-Space
	/// @param theX The Y Coordinate in World-Space
	int PixelToGridX(int theX, int theY);
	/// @return The translated Grid Y
	/// @param theX The X Coordinate in World-Space
	/// @param theX The Y Coordinate in World-Space
	int PixelToGridY(int theX, int theY);

	/// @return The translated World-Space X
	/// @param theGridX The Grid X Coordinate
	/// @param theGridX The Grid Y Coordinate
	int GridToPixelX(int theGridX, int theGridY);
	/// @return The translated World-Space Y
	/// @param theGridX The Grid X Coordinate
	/// @param theGridX The Grid Y Coordinate
	int GridToPixelY(int theGridX, int theGridY);

	/*inline*/ int PixelToGridXKeepOnBoard(int theX, int theY);
	/*inline*/ int PixelToGridYKeepOnBoard(int theX, int theY);
	/// @brief Update every GameObject on the Board
	void UpdateGameObjects();
	/// @param x The X coordinate
	/// @param y The Y coordinate
	/// @param theHitResult The HitResult to fill with data
	/// @return	True if the mouse hits something
	bool MouseHitTest(int x, int y, HitResult *theHitResult);
	/// @brief Handle a mouse down press with a Plant in Cursor
	void MouseDownWithPlant(int x, int y, int theClickCount);
	/// @brief Handle a mouse down press with a tool
	void MouseDownWithTool(int x, int y, int theClickCount, CursorType theCursorType);
	inline void MouseDownNormal(int x, int y, int theClickCount)
	{ /* 未发现 */
		;
	}
	bool CanInteractWithBoardButtons();
	/// @brief Draw the progress bar
	/// @param g Graphics object
	void DrawProgressMeter(Graphics *g);
	/// @brief Update the Board Tooltip
	void UpdateToolTip();
	Plant *GetTopPlantAt(int theGridX, int theGridY, PlantPriority thePriority);
	/// @brief Get all plants on a specific grid coordinate
	/// @param theGridX The X grid coordinate
	/// @param theGridY The Y grid coordinate
	/// @return PlantsOnLawn pointer
	void GetPlantsOnLawn(int theGridX, int theGridY, PlantsOnLawn *thePlantOnLawn);
	/*inline*/ int CountSunFlowers();
	/// @return The SeedPacket's X coordinate in the SeedBank
	/// @param theIndex Index in SeedBank
	int GetSeedPacketPositionX(int theIndex);
	/// @brief Calculate and place all the GraveStones for the level
	/// @param theGridX The X grid coordinate
	/// @param theGridY The Y grid coordinate
	/// @param theLevelRNG Random Number Generator instance reference
	void AddGraveStones(int theGridX, int theCount, MTRand &theLevelRNG);
	/// @return Amount of GraveStones
	int GetGraveStoneCount();
	/// @brief Make the Zombies win
	/// @param theZombie The Zombie that will walk into the house
	void ZombiesWon(Zombie *theZombie = nullptr);
	/// @brief Draw the level title
	/// @param g Graphics object
	void DrawLevel(Graphics *g);
	/// @brief Draw the Shovel
	/// @param g Graphics object
	void DrawShovel(Graphics *g);
	/// @brief Update the Zombie Spawning
	void UpdateZombieSpawning();
	/// @brief Update the natural sun spawning
	void UpdateSunSpawning();
	/*inline*/ void ClearAdvice(AdviceType theHelpIndex);
	/// @return	True if theRow can have a theZombieType
	bool RowCanHaveZombieType(int theRow, ZombieType theZombieType);
	/*inline*/ int NumberZombiesInWave(int theWaveIndex);
	/// @return The total amount of health that the Zombies from theWaveIndex have
	int TotalZombiesHealthInWave(int theWaveIndex);
	/// @brief Draw the debug text based on mDebugTextMode
	/// @param g Graphics object
	void DrawDebugText(Graphics *g);
	/// @brief Draw the CoinBank
	/// @param g Graphics object
	void DrawUICoinBank(Graphics *g);
	/*inline*/ void ShowCoinBank(int theDuration = 1000);
	/// @brief Start the level fade-out sequence or go to the next stage in LastStand/IZombie/Vasebreaker/Survival
	void FadeOutLevel();
	/// @brief Draw the Fade-Out transition
	/// @param g Graphics object
	void DrawFadeOut(Graphics *g);
	/// @brief Draw the ice
	/// @param g Graphics object
	/// @param theGridY The row to draw the ice on
	void DrawIce(Graphics *g, int theGridY);
	/// @return True if the grid at coordinates theGridX and theGridY is ice
	bool IsIceAt(int theGridX, int theGridY);
	/*inline*/ ZombieID ZombieGetID(Zombie *theZombie);
	/*inline*/ Zombie *ZombieGet(ZombieID theZombieID);
	/*inline*/ Zombie *ZombieTryToGet(ZombieID theZombieID);
	/// @brief Draw the debug rectangles on the lawn based on mDebugTextMode
	/// @param g Graphics object
	void DrawDebugObjectRects(Graphics *g);
	/// @brief Update the iced rows on the Board
	void UpdateIce();
	/*inline*/ int GetIceZPos(int theRow);
	/*inline*/ bool CanAddBobSled();
	/*inline*/ void ShakeBoard(int theShakeAmountX, int theShakeAmountY);
	/// @brief Count every non-triggered lawnmower
	int CountUntriggerLawnMowers();
	/// @return True if we find a new Zombie
	/// @param theZombie Reference to a Zombie to iterate
	bool IterateZombies(Zombie *&theZombie);

	/// @return True if we find a new Plant
	/// @param thePlant Reference to a Plant to iterate
	bool IteratePlants(Plant *&thePlant);

	
	/// @return True if we find a new Projectile
	/// @param theProjectile Reference to a Projectile to iterate
	bool IterateProjectiles(Projectile *&theProjectile);
	/// @return True if we find a new Coin
	/// @param theCoin Reference to a Coin to iterate
	bool IterateCoins(Coin *&theCoin);
	/// @return True if we find a new LawnMower
	/// @param theLawnMower Reference to a LawnMower to iterate
	bool IterateLawnMowers(LawnMower *&theLawnMower);
	/// @return True if we find a new Particle System
	/// @param theParticle Reference to a Particle to iterate
	bool IterateParticles(TodParticleSystem *&theParticle);
	/// @return True if we find a new Reanimation
	/// @param theReanimation Reference to a Reanimation to iterate
	bool IterateReanimations(Reanimation *&theReanimation);
	/// @return True if we find a new GridItem
	/// @param theGridItem Reference to a GridItem to iterate
	bool IterateGridItems(GridItem *&theGridItem);
	/*inline*/ Zombie *AddZombieInRow(ZombieType theZombieType, int theRow, int theFromWave);
	/*inline*/ bool IsPoolSquare(int theGridX, int theGridY);
	/// @brief Initiates the level's zombie waves
	void PickZombieWaves();
	/// @brief Stop all Zombie Sounds on the Board
	void StopAllZombieSounds();
	/*inline*/ bool HasLevelAwardDropped();
	/// @brief Update the progress meter values
	void UpdateProgressMeter();
	/// @brief Draw the Bottom UI
	/// @param g Graphics object
	void DrawUIBottom(Graphics *g);
	/// @brief Draw the Top UI
	/// @param g Graphics object
	void DrawUITop(Graphics *g);
	Zombie *ZombieHitTest(int theMouseX, int theMouseY);
	/// @brief Kill all Plants in a radius
	/// @param theX The Circle's X Coordinate
	/// @param theY	The Circle's Y Coordinate
	/// @param theRadius The Circle's Radius
	void KillAllPlantsInRadius(int theX, int theY, int theRadius);
	Plant *GetPumpkinAt(int theGridX, int theGridY);
	Plant *GetFlowerPotAt(int theGridX, int theGridY);
	/// @return True if theZombieType can spawn in theLevel
	static bool CanZombieSpawnOnLevel(ZombieType theZombieType, int theLevel);
	bool IsZombieWaveDistributionOk();
	void PickBackground();
	void InitZombieWaves();
	void InitSurvivalStage();
	static /*inline*/ int MakeRenderOrder(RenderLayer theRenderLayer, int theRow, int theLayerOffset);
	/// @brief Update the gameplay (Objects, events, etc)
	void UpdateGame();
	void InitZombieWavesForLevel(int theForLevel);
	/// @return Flags that determine the recommendation of the seed (see NotRecommend)
	/// @param theSeedType The SeedType to check
	unsigned int SeedNotRecommendedForLevel(SeedType theSeedType);
	/// @brief Draw the Top-Right UI
	/// @param g Graphics object
	void DrawTopRightUI(Graphics *g);
	/// @brief Draw the level Fog
	/// @param g Graphics object
	void DrawFog(Graphics *g);
	/// @brief Update the level Fog
	void UpdateFog();
	/*inline*/ int LeftFogColumn();
	static /*inline*/ bool IsZombieTypePoolOnly(ZombieType theZombieType);
	/// @brief Try to drop a loot piece
	/// @param thePosX World-Space X coordinate
	/// @param thePosY World-Space Y coordinate
	/// @param theDropFactor Rarity multiplier, higher values make drops rarer
	void DropLootPiece(int thePosX, int thePosY, int theDropFactor);
	/// @brief Update the End Sequence (Timers, LawnMower Coins)
	void UpdateLevelEndSequence();
	LawnMower *GetBottomLawnMower();
	/// @return True if we can drop loot
	bool CanDropLoot();
	/// @return Get the ZombieType introduced in this level or ZombieType::ZOMBIE_INVALID if none
	ZombieType GetIntroducedZombieType();
	/// @brief Pick a random GraveStone to be special
	void PickSpecialGraveStone();
	/// @return Y Offset for the row
	/// @param thePosX X position on the row
	/// @param theRow Row to calculate with
	float GetPosYBasedOnRow(float thePosX, int theRow);
	/// @brief Announce a new incoming wave
	void NextWaveComing();
	/// @return True if a BungeeZombie is targetting this cell
	/// @param theGridX The Grid X Coordinate
	/// @param theGridY The Grid Y Coordinate
	bool BungeeIsTargetingCell(int theGridX, int theGridY);
	/*inline*/ int PlantingPixelToGridX(int theX, int theY, SeedType theSeedType);
	/*inline*/ int PlantingPixelToGridY(int theX, int theY, SeedType theSeedType);
	Plant *FindUmbrellaPlant(int theGridX, int theGridY);
	/// @brief Set the tutorial state
	/// @return theTutorialState The current state (see TutorialState enum)
	void SetTutorialState(TutorialState theTutorialState);
	/// @brief Do the Jalapeno Fwoosh on a row
	/// @param theRow The row to create the effect on
	void DoFwoosh(int theRow);
	/// @brief Update the Jalapeno Fwoosh instances
	void UpdateFwoosh();
	Plant *SpecialPlantHitTest(int x, int y);
	/// @brief Update the mouse objects positions
	void UpdateMousePosition();
	/*inline*/ Plant *ToolHitTestHelper(HitResult *theHitResult);
	/*inline*/ Plant *ToolHitTest(int theX, int theY);
	/// @brief Can the grid coordinate have a GraveStone
	/// @param theGridX The X grid coordinate
	/// @param theGridY The Y grid coordinate
	/// @return True if the grid can have a GraveStone
	bool CanAddGraveStoneAt(int theGridX, int theGridY);
	/// @brief Update all GridItems
	void UpdateGridItems();
	/*inline*/ GridItem *AddAGraveStone(int theGridX, int theGridY);
	/// @return Number of Survival Flags completed
	int GetSurvivalFlagsCompleted();
	/// @return True if the level can have a progress bar
	bool HasProgressMeter();
	/// @brief Update the Board's Cursor
	void UpdateCursor();
	/// @brief Update the tutorial state
	void UpdateTutorial();
	/// @return SeedType the Cursor holds currently
	SeedType GetSeedTypeInCursor();
	/*inline*/ int CountPlantByType(SeedType theSeedType);
	/// @return True if the SeedType can be planted
	/// @param theSeedType The SeedType to check
	bool PlantingRequirementsMet(SeedType theSeedType);
	/// @return True if the CobCannon has the minimum requirements to be planted
	bool HasValidCobCannonSpot();
	/// @return True if theGridX and theGridY are valid CobCannon coordinates
	bool IsValidCobCannonSpot(int theGridX, int theGridY);
	/// @return True if theGridX and theGridY can form a set of CobCannonCoordinates
	bool IsValidCobCannonSpotHelper(int theGridX, int theGridY);
	/// @brief Shoot the CobCannon if it fits the requirements
	void MouseDownCobcannonFire(int x, int y, int theClickCount);
	/// @return std::vector of Zombies that are in the radius
	/// @param theX The Circle's X Coordinate
	/// @param theY	The Circle's Y Coordinate
	/// @param theRadius The Circle's Radius
	/// @param theRowRange Max row distance it can check
	/// @param theDamageRangeFlags Damage Flags to filter the Zombies
	std::vector<Zombie*> GetZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, int theDamageRangeFlags);
	/// @brief Kill all Zombies found in the radius
	/// @param theX The Circle's X Coordinate
	/// @param theY	The Circle's Y Coordinate
	/// @param theRadius The Circle's Radius
	/// @param theRowRange Max row distance it can check
	/// @param theDamageRangeFlags Damage Flags to filter the Zombies
	void KillAllZombiesInRadius(int theRow, int theX, int theY, int theRadius, int theRowRange, bool theBurn, int theDamageRangeFlags);
	/*inline*/ int GetSeedBankExtraWidth();
	/// @return True if the given wave index is a flag wave.
	bool IsFlagWave(int theWaveNumber);
	/// @brief Draw the top layer of the door
	/// @param g Graphics object
	void DrawHouseDoorTop(Graphics *g);
	/// @brief Draw the buttom layer of the door
	/// @param g Graphics object
	void DrawHouseDoorBottom(Graphics *g);
	Zombie *GetBossZombie();
	/// @return Amount of alive Gargantuars
	int GetLiveGargantuarCount();
	/// @return True if the level has a ConveyorBelt
	bool HasConveyorBeltSeedBank();
	/*inline*/ bool StageHasRoof();
	/// @brief Spawn the end-flag Zombies from the pool
	void SpawnZombiesFromPool();
	/// @brief Spawn all final-flag Zombies from the Sky
	void SpawnZombiesFromSky();
	/// @brief Pick-Up a specific GameObjectType tool
	void PickUpTool(GameObjectType theObjectType);
	/// @brief Displays the tutorial arrow
	void TutorialArrowShow(int theX, int theY);
	/// @brief Remove the tutorial arrow
	void TutorialArrowRemove();
	/// @return Total value of the Coins that are being collected
	int CountCoinsBeingCollected();
	/// @brief Drop a BungeeZombie with a theZombieType on the Board
	/// @param theBungeeDropGrid Struct containing weighted arrays for determining the spot
	/// @param theZombieType The ZombieType that is dropped by the Bungee
	void BungeeDropZombie(BungeeDropGrid *theBungeeDropGrid, ZombieType theZombieType);
	/// @brief Setup the Stuct for determining BungeeZombie dropping
	/// @param theBungeeDropGrid Struct that is getting initialized
	void SetupBungeeDrop(BungeeDropGrid *theBungeeDropGrid);
	/*inline*/ void PutZombieInWave(ZombieType theZombieType, int theWaveNumber, ZombiePicker *theZombiePicker);
	/*inline*/ void PutInMissingZombies(int theWaveNumber, ZombiePicker *theZombiePicker);
	Rect GetShovelButtonRect();
	void GetZenButtonRect(GameObjectType theObjectType, Rect &theRect);
	Plant *NewPlant(int theGridX, int theGridY, SeedType theSeedType, SeedType theImitaterType = SeedType::SEED_NONE);
	/// @brief Summon Planting Effects at set coordinates, optionally for a specific plant
	/// @param theGridX The grid X coordinate
	/// @param theGridY The grid Y coordinate
	/// @param thePlant [OPTIONAL] Plant pointer for additional offsets
	void DoPlantingEffects(int theGridX, int theGridY, Plant *thePlant);
	/// @return True if it's the final Survival Stage
	bool IsFinalSurvivalStage();
	/// @brief Save the survival score to the current profile
	void SurvivalSaveScore();
	/// @brief Count every non-dying, non-mind-controlled zombie on the Board
	int CountZombiesOnScreen();
	/*inline*/ int GetNumWavesPerSurvivalStage();
	/// @return The level (or Survival/LastStand stage) random number generation seed
	int GetLevelRandSeed();
	/// @brief Add a render object for ZombieType::ZOMBIE_BOSS
	/// @param theRenderList List containing all render items
	/// @param theCurRenderItem The last index of the render list
	/// @param theBossZombie Zombie to use to determine RenderItems
	void AddBossRenderItem(RenderItem *theRenderList, int &theCurRenderItem, Zombie *theBossZombie);
	/*inline*/ GridItem *GetCraterAt(int theGridX, int theGridY);
	/*inline*/ GridItem *GetGraveStoneAt(int theGridX, int theGridY);
	/*inline*/ GridItem *GetLadderAt(int theGridX, int theGridY);
	/*inline*/ GridItem *AddALadder(int theGridX, int theGridY);
	/*inline*/ GridItem *AddACrater(int theGridX, int theGridY);
	/// @brief Initiate the LawnMowers for the current level
	void InitLawnMowers();
	/*inline*/ bool IsPlantInCursor();
	/// @brief Highlight the Plants at mouse coordinates if they fit the requirements
	void HighlightPlantsForMouse(int theMouseX, int theMouseY);
	/// @brief Draw the debug rectangles on the lawn based on mDebugTextMode
	/// @param thePlant The plant for position reference
	/// @param theSize The amount of fog to remove (In pixels)
	void ClearFogAroundPlant(Plant *thePlant, int theSize);
	/*inline*/ void RemoveParticleByType(ParticleEffect theEffectType);
	/*inline*/ GridItem *GetScaryPotAt(int theGridX, int theGridY);
	/// @brief Save the puzzle streak to the current profile
	void PuzzleSaveStreak();
	/*inline*/ void ClearAdviceImmediately();
	/*inline*/ bool IsFinalScaryPotterStage();
	/*inline*/ void DisplayAdviceAgain(const SexyString &theAdvice,
									   MessageStyle theMessageStyle,
									   AdviceType theHelpIndex);
	GridItem *GetSquirrelAt(int theGridX, int theGridY);
	GridItem *GetZenToolAt(int theGridX, int theGridY);
	/// @return True if the Plant is in the Gold Watering Can's range
	bool IsPlantInGoldWateringCanRange(int theMouseX, int theMouseY, Plant *thePlant);
	/// @return True if Zombies can walk from the right
	bool StageHasZombieWalkInFromRight();
	/// @brief Place a rake on the Board if has one purchased
	void PlaceRake();
	GridItem *GetRake();
	/*inline*/ bool IsScaryPotterDaveTalking();
	/*inline*/ Zombie *GetWinningZombie();
	/*inline*/ void ResetFPSStats();
	/// @return Number of plants that are of type theSeedType and don't have a plant above on the Board
	int CountEmptyPotsOrLilies(SeedType theSeedType);
	GridItem *GetGridItemAt(GridItemType theGridItemType, int theGridX, int theGridY);
	/// @return True if the progress meter can have flags
	bool ProgressMeterHasFlags();
	/*inline*/ bool IsLastStandFinalStage();
	/*inline*/ int GetNumWavesPerFlag();
	/// @return The SeedType's Cost
	/// @param theSeedType The SeedType to check
	/// @param theSeedType The theImitaterType to check incase theSeedType == SeedType::SEED_IMITATER
	int GetCurrentPlantCost(SeedType theSeedType, SeedType theImitaterType);
	/*inline*/ bool PlantUsesAcceleratedPricing(SeedType theSeedType);
	void FreezeEffectsForCutscene(bool theFreeze);
	void LoadBackgroundImages();
	/// @brief Can we use this GameObject (see GameObjectType enum)
	/// @param theGameObject The Type of GameObject to check
	bool CanUseGameObject(GameObjectType theGameObject);
	/// @brief Toggle the Mustache Mode
	/// @param theEnableMustache The state of the mode
	void SetMustacheMode(bool theEnableMustache);
	/// @return Amount of Coin Objects of a type
	/// @param CoinType The CoinType to count
	int CountCoinByType(CoinType theCoinType);
	/// @brief Toggle the SuperMower Mode
	/// @param theEnableSuperMower The state of the mode
	void SetSuperMowerMode(bool theEnableSuperMower);
	/// @brief Draw the ZenGarden WheelBarrow button
	/// @param g Graphics object
	/// @param theOffsetY Y offset
	void DrawZenWheelBarrowButton(Graphics *g, int theOffsetY);
	/// @brief Draw the ZenGarden buttons
	/// @param g Graphics object
	void DrawZenButtons(Graphics *g);
	/*inline*/ void OffsetYForPlanting(int &theY, SeedType theSeedType);
	/// @brief Toggle the Future Mode
	/// @param theEnableFuture The state of the mode
	void SetDanceMode(bool theEnableDance);
	/// @brief Toggle the Future Mode
	/// @param theEnableFuture The state of the mode
	void SetFutureMode(bool theEnableFuture);
	/// @brief Toggle the Future Mode
	/// @param theEnableFuture The state of the mode
	void SetPinataMode(bool theEnablePinata);
	/// @brief Toggle the Daisy Mode
	/// @param theEnableDaisy The state of the mode
	void SetDaisyMode(bool theEnableDaisy);
	/// @brief Toggle the Suknbir Mode
	/// @param theEnableSukhbir The state of the mode
	void SetSukhbirMode(bool theEnableSukhbir);
	/// @param x The X coordinate
	/// @param y The Y coordinate
	/// @param theHitResult The HitResult to fill with data
	/// @return True if a Plant is present at coordinates
	bool MouseHitTestPlant(int x, int y, HitResult *theHitResult);

	/*inline*/ Reanimation *CreateRakeReanim(float theRakeX, float theRakeY, int theRenderOrder);
	/// @brief Save to profile the values changed during gameplay
	void CompleteEndLevelSequenceForSaving();
	/// @brief Remove all zombies that can't persist a repick
	void RemoveZombiesForRepick();
	/// @return Amount of GraveStones on Board
	int GetGraveStonesCount();
	/*inline*/ bool IsSurvivalStageWithRepick();
	/*inline*/ bool IsLastStandStageWithRepick();
	/// @brief Process a KeyCode for typing checks
	/// @param theKey KeyCode that has been pressed
	void DoTypingCheck(KeyCode theKey);
	/// @return Number of zombies of a type
	/// @param theZombieType The type to count
	int CountZombieByType(ZombieType theZombieType);
	static /*inline*/ bool IsZombieTypeSpawnedOnly(ZombieType theZombieType);
};
extern bool gShownMoreSunTutorial;

int GetRectOverlap(const Rect &rect1, const Rect &rect2);
bool GetCircleRectOverlap(int theCircleX, int theCircleY, int theRadius, const Rect &theRect);
/*inline*/ void BoardInitForPlayer();

#endif // __BOARD_H__